// Copyright (C) 2019 PISM Authors
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

#include "ISMIP6Climate.hh"

#include "pism/util/IceGrid.hh"
#include "pism/coupler/util/options.hh"
#include "pism/util/io/io_helpers.hh"
#include "pism/geometry/Geometry.hh"

namespace pism {
namespace surface {

ISMIP6::ISMIP6(IceGrid::ConstPtr grid, std::shared_ptr<atmosphere::AtmosphereModel> input)
  : SurfaceModel(grid),
    m_mass_flux_reference(m_grid, "climatic_mass_balance", WITHOUT_GHOSTS),
    m_temperature_reference(m_grid, "ice_surface_temp", WITHOUT_GHOSTS),
    m_surface_reference(m_grid, "usurf", WITHOUT_GHOSTS)
{
  (void) input;

  // allocate model outputs
  m_temperature = allocate_temperature(m_grid);
  m_mass_flux   = allocate_mass_flux(m_grid);

  // set metadata of reference fields
  {
    m_mass_flux_reference.set_attrs("climate_forcing",
                                    "reference surface mass balance rate",
                                    "kg m-2 s-1", "kg m-2 year-1",
                                    "land_ice_surface_specific_mass_balance_flux", 0);

    auto smb_max = m_config->get_number("surface.given.smb_max", "kg m-2 second-1");
    m_mass_flux_reference.metadata().set_numbers("valid_range", {-smb_max, smb_max});
    m_mass_flux_reference.set_time_independent(true);

    m_surface_reference.set_attrs("climate_forcing",
                                  "reference surface altitude",
                                  "m", "m", "surface_altitude", 0);

    m_surface_reference.metadata().set_numbers("valid_range", {0.0, m_grid->Lz()});
    m_surface_reference.set_time_independent(true);

    m_temperature_reference.set_attrs("climate_forcing",
                                      "reference temperature",
                                      "Kelvin", "Kelvin", "", 0);

    m_temperature_reference.metadata().set_numbers("valid_range", {0.0, 373.15});
    m_temperature_reference.set_time_independent(true);
  }

  // allocate storage for time-dependent inputs
  ForcingOptions opt(*m_grid->ctx(), "surface.ismip6");

  {
    unsigned int buffer_size = m_config->get_number("input.forcing.buffer_size");
    unsigned int evaluations_per_year = m_config->get_number("input.forcing.evaluations_per_year");
    bool periodic = opt.period > 0;

    File file(m_grid->com, opt.filename, PISM_NETCDF3, PISM_READONLY);

    {
      m_mass_flux_anomaly = IceModelVec2T::ForcingField(m_grid,
                                                        file,
                                                        "climatic_mass_balance_anomaly",
                                                        "", // no standard name
                                                        buffer_size,
                                                        evaluations_per_year,
                                                        periodic);

      m_mass_flux_anomaly->set_attrs("climate_forcing",
                                     "surface mass balance rate anomaly",
                                     "kg m-2 s-1", "kg m-2 year-1",
                                     "", 0);

    }

    {
      m_mass_flux_gradient = IceModelVec2T::ForcingField(m_grid,
                                                         file,
                                                         "climatic_mass_balance_gradient",
                                                         "", // no standard name
                                                         buffer_size,
                                                         evaluations_per_year,
                                                         periodic);

      m_mass_flux_gradient->set_attrs("climate_forcing",
                                      "surface mass balance rate elevation lapse rate",
                                      "kg m-2 s-1 m-1", "kg m-2 year-1 m-1",
                                      "", 0);
    }

    {
      m_temperature_anomaly = IceModelVec2T::ForcingField(m_grid,
                                                          file,
                                                          "ice_surface_temp_anomaly",
                                                          "", // no standard name
                                                          buffer_size,
                                                          evaluations_per_year,
                                                          periodic);

      m_temperature_anomaly->set_attrs("climate_forcing",
                                       "ice surface temperature anomaly",
                                       "Kelvin", "Kelvin", "", 0);
    }

    {
      m_temperature_gradient = IceModelVec2T::ForcingField(m_grid,
                                                           file,
                                                           "ice_surface_temp_gradient",
                                                           "", // no standard name
                                                           buffer_size,
                                                           evaluations_per_year,
                                                           periodic);

      m_temperature_gradient->set_attrs("climate_forcing",
                                        "ice surface temperature elevation lapse rate",
                                        "Kelvin m-1", "Kelvin m-1", "", 0);
    }

  }
}

ISMIP6::~ISMIP6() {
  // empty
}

void ISMIP6::init_impl(const Geometry &geometry) {
  (void) geometry;

  m_log->message(2, "* Initializing the ISMIP6 surface model...\n");

  {
    // File with reference surface elevation, temperature, and climatic mass balance
    auto reference_filename = m_config->get_string("surface.ismip6.reference_file");
    File reference_file(m_grid->com, reference_filename, PISM_GUESS, PISM_READONLY);

    m_mass_flux_reference.regrid(reference_file, CRITICAL);
    m_surface_reference.regrid(reference_file, CRITICAL);
    m_temperature_reference.regrid(reference_file, CRITICAL);
  }

  {
    ForcingOptions opt(*m_grid->ctx(), "surface.ismip6");

    m_mass_flux_anomaly->init(opt.filename, opt.period, opt.reference_time);
    m_mass_flux_gradient->init(opt.filename, opt.period, opt.reference_time);

    m_temperature_anomaly->init(opt.filename, opt.period, opt.reference_time);
    m_temperature_gradient->init(opt.filename, opt.period, opt.reference_time);
  }
}

void ISMIP6::update_impl(const Geometry &geometry, double t, double dt) {

  // inputs
  const IceModelVec2S &h       = geometry.ice_surface_elevation;
  const IceModelVec2S &h_ref   = m_surface_reference;
  const IceModelVec2S &T_ref   = m_temperature_reference;
  const IceModelVec2S &SMB_ref = m_mass_flux_reference;

  IceModelVec2T &dTdz   = *m_temperature_gradient;
  IceModelVec2T &dSMBdz = *m_mass_flux_gradient;
  IceModelVec2T &aT     = *m_temperature_anomaly;
  IceModelVec2T &aSMB   = *m_mass_flux_anomaly;

  // outputs
  IceModelVec2S &T   = *m_temperature;
  IceModelVec2S &SMB = *m_mass_flux;

  // get time-dependent input fields at the current time
  {
    aT.update(t, dt);
    aSMB.update(t, dt);
    dTdz.update(t, dt);
    dSMBdz.update(t, dt);

    aT.average(t, dt);
    aSMB.average(t, dt);
    dTdz.average(t, dt);
    dSMBdz.average(t, dt);
  }

  // From http://www.climate-cryosphere.org/wiki/index.php?title=ISMIP6-Projections-Greenland:
  // SMB(x,y,t) = SMB_ref(x,y) + aSMB(x,y,t) + dSMBdz(x,y,t) * [h(x,y,t) - h_ref(x,y)]

  IceModelVec::AccessList list{&h, &h_ref,
                               &SMB, &SMB_ref, &aSMB, &dSMBdz,
                               &T, &T_ref, &aT, &dTdz};

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    SMB(i, j) = SMB_ref(i, j) + aSMB(i, j) + dSMBdz(i, j) * (h(i, j) - h_ref(i, j));
    T(i, j)   = T_ref(i, j) + aT(i, j) + dTdz(i, j) * (h(i, j) - h_ref(i, j));
  }

  dummy_accumulation(SMB, *m_accumulation);
  dummy_melt(SMB, *m_melt);
  dummy_runoff(SMB, *m_runoff);
}

MaxTimestep ISMIP6::max_timestep_impl(double t) const {
  using std::min;

  auto dt = m_temperature_anomaly->max_timestep(t);
  dt = min(dt, m_temperature_gradient->max_timestep(t));
  dt = min(dt, m_mass_flux_anomaly->max_timestep(t));
  dt = min(dt, m_mass_flux_gradient->max_timestep(t));

  if (dt.finite()) {
    return MaxTimestep(dt.value(), "surface ISMIP6");
  } else {
    return MaxTimestep("surface ISMIP6");
  }
}

const IceModelVec2S &ISMIP6::mass_flux_impl() const {
  return *m_mass_flux;
}

const IceModelVec2S &ISMIP6::temperature_impl() const {
  return *m_temperature;
}

const IceModelVec2S &ISMIP6::accumulation_impl() const {
  return *m_accumulation;
}

const IceModelVec2S &ISMIP6::melt_impl() const {
  return *m_melt;
}

const IceModelVec2S &ISMIP6::runoff_impl() const {
  return *m_runoff;
}

} // end of namespace surface
} // end of namespace pism
