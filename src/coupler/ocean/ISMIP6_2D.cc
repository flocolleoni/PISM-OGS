// Copyright (C) 2008-2020 Ed Bueler, Constantine Khroulev, Ricarda Winkelmann,
// Gudfinna Adalgeirsdottir, Andy Aschwanden and Torsten Albrecht
//
// This file is part of PISM.
//
// PISM is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or (at your option) any later
// version.
//
// PISM is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License
// along with PISM; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include <cassert>

#include "ISMIP6_2D.hh"
#include "pism/util/pism_options.hh"
#include "pism/util/io/io_helpers.hh"
#include "pism/util/MaxTimestep.hh"
#include "pism/util/pism_utilities.hh"

#include "pism/util/ConfigInterface.hh"
#include "pism/util/IceGrid.hh"
#include "pism/util/Mask.hh"
#include "pism/util/Vars.hh"
#include "pism/util/iceModelVec.hh"
#include "pism/util/Time.hh"
#include "pism/geometry/Geometry.hh"

#include "pism/coupler/util/options.hh"


namespace pism {
namespace ocean {


ISMIP6_2D::ISMIP6_2D(IceGrid::ConstPtr g)
  :  CompleteOceanModel(g, std::shared_ptr<OceanModel>()),
     m_basin_numbers(m_grid, "basin_numbers", WITH_GHOSTS),
     m_deltaT_basin(m_grid, "deltaT_basin", WITH_GHOSTS), // check why we have GHOSTS
     m_thermal_forcing(m_grid, "thermal_forcing", WITHOUT_GHOSTS) {

  m_shelf_base_temperature = allocate_shelf_base_temperature(g);
  m_shelf_base_mass_flux   = allocate_shelf_base_mass_flux(g);

  ForcingOptions opt(*m_grid->ctx(), "ocean.ismip6_2d");

  {
    unsigned int buffer_size = m_config->get_number("input.forcing.buffer_size");
    unsigned int evaluations_per_year = m_config->get_number("input.forcing.evaluations_per_year");
    bool periodic = opt.period > 0;

    File file(m_grid->com, opt.filename, PISM_NETCDF3, PISM_READONLY);

    m_shelfbtemp = IceModelVec2T::ForcingField(m_grid,
                                               file,
                                               "shelfbtemp",
                                               "", // no standard name
                                               buffer_size,
                                               evaluations_per_year,
                                               periodic,
                                               LINEAR);

   m_salinity_ocean = IceModelVec2T::ForcingField(m_grid,
                                                 file,
                                                  "salinity_ocean",
                                                  "", // no standard name
                                                   buffer_size,
                                                  evaluations_per_year,
                                                  periodic,
                                                  LINEAR);

  }

  m_shelfbtemp->set_attrs("climate_forcing",
                          "absolute temperature at ice shelf base",
                          "degC", "degC", "", 0);
  m_salinity_ocean->set_attrs("climate_forcing",
                              "ocean salinity",
                              "g/kg", "g/kg", "", 0);


// Basins id should starts from 0 in the input file
  m_basin_numbers.set_attrs("climate_forcing", "mask of drainage basins",
                         "", "", "", 0);
  m_n_basins = 0;

  m_deltaT_basin.set_attrs("climate_forcing", "basins delta T offset", "K", "K", "", 0);


}

ISMIP6_2D::~ISMIP6_2D() {
  // empty
}

void ISMIP6_2D::init_impl(const Geometry &geometry) {

  m_log->message(2,
             "* Initializing the ISMIP6 ocean reading temperature at ice-shelves base\n");

  ForcingOptions opt(*m_grid->ctx(), "ocean.ismip6_2d");

  m_shelfbtemp->init(opt.filename, opt.period, opt.reference_time);
  m_salinity_ocean->init(opt.filename, opt.period, opt.reference_time);



 // ISMIP6 ocean thermal forcing method
  std:: string strg_method = m_config->get_string("ocean.ismip6_2d.thermal_forcing_method");
  m_log->message(2, "  - Using thermal forcing method '%s'...\n", strg_method.c_str());

  if (strg_method == "non-local") {
   m_method = 0;
  } else if (strg_method == "local") {
    m_method = 1;
  } else {
      // should not be reached
      throw RuntimeError(PISM_ERROR_LOCATION, "ISMIP6 invalid method");
  }



 // Get gamma0 from config file or prescribed by user
  m_gamma_0   = m_config->get_number("ocean.ismip6_2d.heat_exchange_coefficent", "meter seconds-1");
  m_log->message(2, "             Using gamma0 (meter seconds-1) '%f'...\n", m_gamma_0);


  //
  //  read ocean basins
  //
  auto basin_N_file = m_config->get_string("ocean.ismip6_2d.basins_file");

  if (not basin_N_file.empty()) {
    m_log->message(2, "  - Reading basins from '%s'...\n", basin_N_file.c_str());
    // Note, for IceModelVec2Int the m_interpolation_type = NEAREST;
    m_basin_numbers.regrid(basin_N_file, CRITICAL);
    m_n_basins = m_basin_numbers.max();
  } else {
    
    // If non-local method selected and basins file is not prescribed --> ERROR
    if (m_method == 0) {
            // should not be reached
      throw RuntimeError(PISM_ERROR_LOCATION, "ISMIP6 non-local method requires a basins_file");
    } else{
      m_log->message(2, "  - Option ocean.ismip6_2d.basin_file is not set. Using default basin_number=0 '%d'...\n", 0);
      m_basin_numbers.set(0); // Note, must be zero, as basin count starts at zero
    }
  }

  //
  //  Read deltaT field and gamma0
  //
  auto deltaT_file = m_config->get_string("ocean.ismip6_2d.deltaT_file");
  if (not deltaT_file.empty()) {
    m_log->message(2, "  - Reading deltaT field from '%s'...\n", deltaT_file.c_str());
    m_deltaT_basin.regrid(deltaT_file, CRITICAL);
  } else {
    m_log->message(2, "  - deltaT file is not set...Using default deltaT=0\n");    
    m_deltaT_basin.set(0.0); // todo: read from config
  }


  // read time-independent data right away:
  if (m_shelfbtemp->n_records() == 1 && m_salinity_ocean->n_records() == 1) {
    update(geometry, m_grid->ctx()->time()->current(), 0); // dt is irrelevant
  }
}



void ISMIP6_2D::update_impl(const Geometry &geometry, double t, double dt) {
  (void) t;
  (void) dt;


  m_shelfbtemp->update(t, dt);  // FLO
  m_salinity_ocean->update(t, dt);  // FLO

  m_shelfbtemp->average(t, dt);  // FLO
  m_salinity_ocean->average(t, dt);  // FLO

  m_shelf_base_temperature->copy_from(*m_shelfbtemp);


  const IceModelVec2S &H = geometry.ice_thickness;
  const IceModelVec2CellType &cell_type = geometry.cell_type;

  std::vector<double> basin_TF(m_n_basins);


  if (m_method == 0) { 

        compute_thermal_forcing(cell_type, H, *m_shelfbtemp, *m_salinity_ocean, m_thermal_forcing);

        compute_avg_thermal_forcing(cell_type, m_basin_numbers, m_thermal_forcing, basin_TF); // per basin

        non_local_quadratic_melt(cell_type, m_thermal_forcing, m_basin_numbers, basin_TF, *m_shelf_base_mass_flux); // call to ISMIP6 quadratic parametrisation

  } else if (m_method == 1) {

        local_quadratic_melt(cell_type, H, *m_shelfbtemp, *m_salinity_ocean, *m_shelf_base_mass_flux); // call to ISMIP6 quadratic parametrisation

  }


  // Set shelf base temperature to the melting temperature at the base (depth within the
  // ice equal to ice thickness).
  
  melting_point_temperature(H, *m_shelf_base_temperature);

  m_melange_back_pressure_fraction->set(m_config->get_number("ocean.melange_back_pressure_fraction"));

}


MaxTimestep ISMIP6_2D::max_timestep_impl(double t) const {
  (void) t;

  return MaxTimestep("ocean ismip6_2d");
}


const IceModelVec2S& ISMIP6_2D::shelf_base_temperature_impl() const {
  return *m_shelf_base_temperature;
}

const IceModelVec2S& ISMIP6_2D::shelf_base_mass_flux_impl() const {
  return *m_shelf_base_mass_flux;
}


// Compute thermal forcing at ice shelves depth
void ISMIP6_2D::compute_thermal_forcing(const IceModelVec2CellType &cell_type,
                                        const IceModelVec2S &ice_thickness,
                                        const IceModelVec2S &shelfbtemp,
                                        const IceModelVec2S &salinity_ocean,
                                        IceModelVec2S &thermal_forcing) {

  const double
    sea_water_density = m_config->get_number("constants.sea_water.density"),
    ice_density       = m_config->get_number("constants.ice.density");

  IceModelVec::AccessList list{&cell_type, &ice_thickness, &shelfbtemp, &salinity_ocean, &thermal_forcing};

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    auto M = cell_type(i, j);

    if (M == MASK_FLOATING) {
      // compute T_f(i, j) according to Favier et al. XXXX and Jourdain et al. XXXX
      // UNESCO Seawater freezing temperature
      double
        shelfbaseelev = - (ice_density / sea_water_density) * ice_thickness(i,j),
        T_f           = 273.15 + (0.0832 -0.0575 * salinity_ocean(i,j) + 7.59e-4 * shelfbaseelev);
         // add 273.15 to convert from Celsius to Kelvin

      double
         Tforcing = shelfbtemp(i,j)+273.15 - T_f;

      thermal_forcing(i,j) = Tforcing;
    } 

  }
}


// This routine should calculate the averaged thermal-forcing
// over the sum of ice shelves points contained in each drainage basins
void ISMIP6_2D::compute_avg_thermal_forcing(const IceModelVec2CellType &cell_type,
                                         const IceModelVec2Int &basin_numbers,
                                         const IceModelVec2S &thermal_forcing,
                                         std::vector<double> &basin_TF) {


  std::vector<int> n_shelf_cells_per_basin(m_n_basins, 0);

  basin_TF.resize(m_n_basins);
  std::fill(basin_TF.begin(), basin_TF.end(), 0.0); // added now


  IceModelVec::AccessList list{&cell_type, &thermal_forcing, &basin_numbers};

  // count the number of cells in the intersection of each shelf with all the basins
  // sum thermal forcing over the floating areas in each basins
  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    auto M = cell_type(i, j);
    if (M == MASK_FLOATING) {

      int basin_id = int(basin_numbers.as_int(i, j));

      n_shelf_cells_per_basin[basin_id]++;
      basin_TF[basin_id] += thermal_forcing(i,j);
    }

  }

  // Compute averaged thermal forcing per basin
 for (int basin_id = 0; basin_id < m_n_basins; basin_id++) {

      n_shelf_cells_per_basin[basin_id] = GlobalSum(m_grid->com, n_shelf_cells_per_basin[basin_id]);
      basin_TF[basin_id] = GlobalSum(m_grid->com, basin_TF[basin_id]);

    if (n_shelf_cells_per_basin[basin_id] > 0) {
      // Compute averaged thermal forcing per basin
      basin_TF[basin_id] /= n_shelf_cells_per_basin[basin_id];
    }

 }

}


//! \brief Computes mass flux in [kg m-2 s-1].
/*!
 * NON-LOCAL ISMIP6 Parameterisation (see Jourdain et al., 2019)
 */
void ISMIP6_2D::non_local_quadratic_melt(const IceModelVec2CellType &cell_type,
                          const IceModelVec2S &thermal_forcing,
                          const IceModelVec2Int &basin_numbers,
                          std::vector<double> &basin_TF,
                          IceModelVec2S &result) {
  const double
    L                 = 3.34e5, // Latent heat of fusion (J/kg)//m_config->get_number("constants.fresh_water.latent_heat_of_fusion"),
    sea_water_density = 1028.0, // Sea water density (kg/m^3) // m_config->get_number("constants.sea_water.density"),
    ice_density       = 918.0,  // Ice density (kg/m^3) // m_config->get_number("constants.ice.density"),
    c_p_ocean         = 3974.0; // J/(K*kg), specific heat capacity of ocean mixed layer

  IceModelVec::AccessList list{&cell_type, &basin_numbers, &thermal_forcing, &m_deltaT_basin, &result};

// Calculate ocean basal melting below ice shelves
  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    int basin_id = int(basin_numbers.as_int(i, j));

    auto M = cell_type(i, j);

    if (M == MASK_FLOATING) {

      const double deltaT    = m_deltaT_basin(i, j);
      const double coeff2    = pow((sea_water_density * c_p_ocean) / (L * ice_density),2);
      double
          ocean_heat_flux = coeff2 * m_gamma_0 * (thermal_forcing(i,j) + deltaT) *abs(basin_TF[basin_id] + deltaT); // in W/m^2

      result(i,j) =  ocean_heat_flux; // m s-1

      // convert from [m s-1] to [kg m-2 s-1]:
      result(i,j) *= ice_density;

    } else {
      result(i,j) = 0.0;
    }

  }
}



//! \brief Computes mass flux in [kg m-2 s-1].
/*!
 * Assumes that mass flux is proportional to the shelf-base heat flux.
 */
void ISMIP6_2D::local_quadratic_melt(const IceModelVec2CellType &cell_type,
                        const IceModelVec2S &ice_thickness,
                        const IceModelVec2S &shelfbtemp,
                        const IceModelVec2S &salinity_ocean,
                        IceModelVec2S &result) const {
  
  const double
    L                 = 3.34e5, // Latent heat of fusion (J/kg)//m_config->get_number("constants.fresh_water.latent_heat_of_fusion"),
    sea_water_density = 1028.0, // Sea water density (kg/m^3) // m_config->get_number("constants.sea_water.density"),
    ice_density       = 918.0,  // Ice density (kg/m^3) // m_config->get_number("constants.ice.density"),
    c_p_ocean         = 3974.0; // J/(K*kg), specific heat capacity of ocean mixed layer


  //FIXME: gamma_T should be a function of the friction velocity, not a const

  IceModelVec::AccessList list{&cell_type, &ice_thickness, &shelfbtemp, &salinity_ocean, &m_deltaT_basin, &result};

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    auto M = cell_type(i, j);

    if (M == MASK_FLOATING) {

      // compute T_f(i, j) according to Favier et al. XXXX and Jourdain et al. XXXX
      // UNESCO Seawater freezing temperature
      double
        shelfbaseelev = - (ice_density / sea_water_density) * ice_thickness(i,j),
        T_f           = 273.15 + (0.0832 -0.0575 * salinity_ocean(i,j) + 7.59e-4 * shelfbaseelev); // add 273.15 to convert from Celsius to Kelvin
        

      const double deltaT    = m_deltaT_basin(i, j);  
      const double coeff2    = pow((sea_water_density * c_p_ocean) / (L * ice_density),2);
      double
        thermal_forcing = shelfbtemp(i,j)+273.15 - T_f,  // add 273.15 to convert from Celsius to Kelvin
        ocean_heat_flux = coeff2  * m_gamma_0 * pow(fmax(thermal_forcing+ deltaT,0.0),2); // in W/m^2

      result(i,j) =  ocean_heat_flux; // m s-1

      // convert from [m s-1] to [kg m-2 s-1]:
      result(i,j) *= ice_density;
    } else {
      result(i,j) =  0.0; // m s-1      
    }
  }
}



/*!
 * Compute melting temperature at a given depth within the ice.
 */
void ISMIP6_2D::melting_point_temperature(const IceModelVec2S &depth,
                                    IceModelVec2S &result) const {
const double
    T0          = m_config->get_number("constants.fresh_water.melting_point_temperature"), // K
    beta_CC     = m_config->get_number("constants.ice.beta_Clausius_Clapeyron"),
    g           = m_config->get_number("constants.standard_gravity"),
    ice_density = m_config->get_number("constants.ice.density");

  IceModelVec::AccessList list{&depth, &result};

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();
    const double pressure = ice_density * g * depth(i,j); // FIXME task #7297
    // result is set to melting point at depth
    result(i,j) = T0 - beta_CC * pressure;
  }
}

} // end of namespace ocean
} // end of namespace pism
