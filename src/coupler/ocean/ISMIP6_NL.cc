// Copyright (C) 2008-2019 Ed Bueler, Constantine Khroulev, Ricarda Winkelmann,
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

#include "ISMIP6_NL.hh"
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


ISMIP6_NL::ISMIP6_NL(IceGrid::ConstPtr g)
  :  CompleteOceanModel(g, std::shared_ptr<OceanModel>()) {

  m_shelf_base_temperature = allocate_shelf_base_temperature(g);
  m_shelf_base_mass_flux   = allocate_shelf_base_mass_flux(g);

  ForcingOptions opt(*m_grid->ctx(), "ocean.ismip6nl");

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

/* m_basin_mask = IceModelVec2T::ForcingField(m_grid,
                                                 file,
                                                 "basin_mask",
                                                 "", // no standard name
                                                 buffer_size,
                                                 evaluations_per_year,
                                                 periodic,
                                                 LINEAR);
*/
  }

  m_shelfbtemp->set_attrs("climate_forcing",
                          "absolute temperature at ice shelf base",
                          "Kelvin", "Kelvin", "", 0);
  m_salinity_ocean->set_attrs("climate_forcing",
                              "ocean salinity",
                              "g/kg", "g/kg", "", 0);

  m_basin_mask.set_attrs("climate_forcing", "mask of drainage basins",
                         "", "", "", 0);
  m_n_basins = 0;
}

ISMIP6_NL::~ISMIP6_NL() {
  // empty
}

void ISMIP6_NL::init_impl(const Geometry &geometry) {

  m_log->message(2,
             "* Initializing the ISMIP6 ocean reading base of the shelf temperature\n");

  ForcingOptions opt(*m_grid->ctx(), "ocean.ismip6");

  m_shelfbtemp->init(opt.filename, opt.period, opt.reference_time);
  m_salinity_ocean->init(opt.filename, opt.period, opt.reference_time);

  m_basin_mask.regrid(opt.filename, CRITICAL);
  m_n_basins = m_basin_mask.max() + 1;
  m_log->message(4, "ISMIP6 ocean basins min=%f,max=%f\n", m_basin_mask.min(), m_basin_mask.max());

  // read time-independent data right away:
  if (m_shelfbtemp->n_records() == 1 && m_salinity_ocean->n_records() == 1) {
    update(geometry, m_grid->ctx()->time()->current(), 0); // dt is irrelevant
  }
}

void ISMIP6_NL::write_model_state_impl(const File &output) const {

  m_basin_mask.write(output);

  OceanModel::define_model_state_impl(output);
}

void ISMIP6_NL::update_impl(const Geometry &geometry, double t, double dt) {
  (void) t;
  (void) dt;

  //m_shelfbtemp->copy_from(m_input_model->shelfbtemp());

  m_shelfbtemp->update(t, dt);  // FLO
  m_salinity_ocean->update(t, dt);  // FLO

  m_shelfbtemp->average(t, dt);  // FLO
  m_salinity_ocean->average(t, dt);  // FLO

  m_shelf_base_temperature->copy_from(*m_shelfbtemp);
  // FLO m_shelf_base_mass_flux->copy_from(*m_shelfbmassflux);

  const IceModelVec2S &H = geometry.ice_thickness;


  // FIXME: m_n_shelves is not really the number of shelves.
//  m_n_shelves = m_geometry->ice_shelf_mask().max() + 1;

  std::vector<double> thermal_forcing(m_n_basins);
  std::vector<double> TF_avg(m_n_basins);

  // Set shelf base temperature to the melting temperature at the base (depth within the
  // ice equal to ice thickness).
  // FLO melting_point_temperature(H, *m_shelf_base_temperature);

  compute_thermal_forcing(H, *m_shelfbtemp, *m_salinity_ocean, thermal_forcing)

  compute_avg_thermal_forcing(m_basin_mask, m_geometry->ice_shelf_mask(), thermal_forcing, TF_avg); // per basin

  mass_flux(thermal_forcing, TF_avg, *m_shelf_base_mass_flux); // call to ISMIP6 quadratic parametrisation

  m_melange_back_pressure_fraction->set(m_config->get_number("ocean.melange_back_pressure_fraction"));


}


MaxTimestep ISMIP6_NL::max_timestep_impl(double t) const {
  (void) t;

  return MaxTimestep("ocean ismip6nl");
}


const IceModelVec2S& ISMIP6_NL::shelf_base_temperature_impl() const {
  return *m_shelf_base_temperature;
}

const IceModelVec2S& ISMIP6_NL::shelf_base_mass_flux_impl() const {
  return *m_shelf_base_mass_flux;
}

/*!
 * Compute melting temperature at a given depth within the ice.
 */
void ISMIP6_NL::melting_point_temperature(const IceModelVec2S &depth,
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


void ISMIP6_NL::compute_thermal_forcing(const IceModelVec2S &ice_thickness, const IceModelVec2S &shelfbtemp, const IceModelVec2S &salinity_ocean, std::vector<double> &thermal_forcing) const {
  const double
//    melt_factor       = m_config->get_number("ocean.pik_melt_factor"),
//    L                 = m_config->get_number("constants.fresh_water.latent_heat_of_fusion"),
    sea_water_density = m_config->get_number("constants.sea_water.density"),
    ice_density       = m_config->get_number("constants.ice.density"),
//    c_p_ocean         = 3974.0, // J/(K*kg), specific heat capacity of ocean mixed layer
//    gamma_0           = 3.52e-4;   // m/s, 11100 m/yr from local_MeanAnt method (Jourdain et al. 2020)
    //ocean_salinity    = 35.0;   // g/kg //********************* TO DO: implement also variable salinity in T_f //
    // FLO T_ocean           = units::convert(m_sys, -1.7, "Celsius", "Kelvin"); //Default in PISM-PIK

  //FIXME: gamma_T should be a function of the friction velocity, not a const

  IceModelVec::AccessList list{&ice_thickness, &shelfbtemp, &salinity_ocean, &result};

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    // compute T_f(i, j) according to beckmann_goosse03, which has the
    // meaning of the freezing temperature of the ocean water directly
    // under the shelf, (of salinity 35psu) [this is related to the
    // Pressure Melting Temperature, see beckmann_goosse03 eq. 2 for
    // details]
  double
     shelfbaseelev = - (ice_density / sea_water_density) * ice_thickness(i,j);
     T_f           = 273.15 + (0.0832 -0.0575 * salinity_ocean(i,j) + 7.59e-4 * shelfbaseelev);
    // add 273.15 to convert from Celsius to Kelvin

    // compute ocean_heat_flux according to beckmann_goosse03
    // positive, if T_oc > T_ice ==> heat flux FROM ocean TO ice
    // FLO double ocean_heat_flux = melt_factor * sea_water_density * c_p_ocean * gamma_T * (T_ocean - T_f); // in W/m^2


// NON-LOCAL ISMIP6 Parameterisation (see Jourdain et al., 2019)

        thermal_forcing = shelfbtemp(i,j) - T_f;

  }
}


//! Compute temperature and salinity input from ocean data by averaging.

//! We average the ocean data over the continental shelf reagion for each basin.
//! We use dummy ocean data if no such average can be calculated.
void ISMIP6_NL::compute_avg_thermal_forcing(const IceModelVec2Int &basin_mask,
                                         const IceModelVec2CellType &mask,
                                         const IceModelVec2S &thermal_forcing,
                                         IceModelVec2S&TF_avg) {


  const IceModelVec2S shelf_mask;
  // Retrieve floating points
  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    if (mask.as_int(i, j) == MASK_FLOATING) {
      shelf_mask(i, j) = 1;
      m_n_shelves++;
    } else {
      shelf_mask(i, j) = 0;
    }
  }


  std::vector<double> basin_TF(m_n_shelves,m_n_basins);
  basin_TF.resize(m_n_basins);
  for (int basin_id = 0; basin_id < m_n_basins; basin_id++) {
    basin_TF[basin_id] = 0.0;
  }

  IceModelVec::AccessList list{ &thermal_forcing, &basin_mask, &mask};
  std::vector<std::vector<int> > n_shelf_cells_per_basin(m_n_shelves, std::vector<int>(m_n_basins, 0));

  // 1) count the number of cells in each shelf
  // 2) count the number of cells in the intersection of each shelf with all the basins
  {
    for (Points p(*m_grid); p; p.next()) {
      const int i = p.i(), j = p.j();
      int s = shelf_mask.as_int(i, j);
      int b = basin_mask.as_int(i, j);
      n_shelf_cells_per_basin[s][b]++;
      basin_TF[s][b] = thermal_forcing(i, j);
    }

    // compute the sum for each basin for region that intersects with the
    // area covered by an ice shelf.
  for (int s = 0; s < m_n_shelves; s++) {
    for (int b = 0; b < m_n_basins; b++) {
      n_shelf_cells_per_basin[s][b] = GlobalSum(m_grid->com, n_shelf_cells_per_basin[s][b]);
      basin_TF[s][b] = GlobalSum(m_grid->com, basin_TF[s][b]);

    }
  }
 }

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    // make sure all temperatures are zero at the beginning of each time step
    TF_avg(i, j) = 0.0; // in K

    int s = shelf_mask.as_int(i, j);

    if (mask.as_int(i, j) == MASK_FLOATING and s > 0) {
      // note: shelf_mask = 0 in lakes

      // weighted input depending on the number of shelf cells in each basin
      for (int b = 1; b < m_n_basins; b++) { //Note: b=0 yields nan
        TF_avg(i, j) += basin_TF[s][b]/ n_shelf_cells_per_basin[s][b];
      }
    }
  }
}



//! \brief Computes mass flux in [kg m-2 s-1].
/*!
 * Assumes that mass flux is proportional to the shelf-base heat flux.
 */
void ISMIP6_NL::mass_flux(std::vector<double> &thermal_forcing, std::vector<double> &TF_avg, IceModelVec2S &result) const {
  const double
//    melt_factor       = m_config->get_number("ocean.pik_melt_factor"),
    L                 = m_config->get_number("constants.fresh_water.latent_heat_of_fusion"),
    sea_water_density = m_config->get_number("constants.sea_water.density"),
    ice_density       = m_config->get_number("constants.ice.density"),
    c_p_ocean         = 3974.0, // J/(K*kg), specific heat capacity of ocean mixed layer
    gamma_0           = 3.52e-4;   // m/s, 11100 m/yr from local_MeanAnt method (Jourdain et al. 2020)
    //ocean_salinity    = 35.0;   // g/kg //********************* TO DO: implement also variable salinity in T_f //
    // FLO T_ocean           = units::convert(m_sys, -1.7, "Celsius", "Kelvin"); //Default in PISM-PIK

  //FIXME: gamma_T should be a function of the friction velocity, not a const

  IceModelVec::AccessList list{&thermal_forcing, &TF_avg, &result};

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    // compute T_f(i, j) according to beckmann_goosse03, which has the
    // meaning of the freezing temperature of the ocean water directly
    // under the shelf, (of salinity 35psu) [this is related to the
    // Pressure Melting Temperature, see beckmann_goosse03 eq. 2 for
    // details]
  //double
  //   shelfbaseelev = - (ice_density / sea_water_density) * ice_thickness(i,j),
  //    T_f           = 273.15 + (0.0832 -0.0575 * salinity_ocean(i,j) + 7.59e-4 * shelfbaseelev);
    // add 273.15 to convert from Celsius to Kelvin

    // compute ocean_heat_flux according to beckmann_goosse03
    // positive, if T_oc > T_ice ==> heat flux FROM ocean TO ice
    // double ocean_heat_flux = melt_factor * sea_water_density * c_p_ocean * gamma_T * (T_ocean - T_f); // in W/m^2

// FLO IMPLEMENTATION
// NON-LOCAL ISMIP6 Parameterisation (see Jourdain et al., 2019)
//    double
//        thermal_forcing = shelfbtemp(i,j) - T_f;

    double
        ocean_heat_flux = pow((sea_water_density * c_p_ocean) / (L * ice_density),2)  * gamma_0 * thermal_forcing*TF_avg; // in W/m^2

    result(i,j) =  ocean_heat_flux; // m s-1

    // convert from [m s-1] to [kg m-2 s-1]:
    result(i,j) *= ice_density;
  }
}

} // end of namespace ocean
} // end of namespace pism
