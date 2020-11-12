// Copyright (C) 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019 PISM Authors
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

#ifndef _POISMIP6_H_
#define _POISMIP6_H_

#include "CompleteOceanModel.hh"
//#include "pism/coupler/OceanModel.hh"
#include "pism/util/iceModelVec2T.hh"

namespace pism {
namespace ocean {
//! \brief Implements the ocean model used for ISMIP6.
//!
//! Uses a parameterization of sub-shelf melting with respect to
//! sub-shelf heat flux like in [@ref Jourdain et al., 2020].
//!
//! Models heat flux into the base of the shelf as
//!
//! @f[ Q_{\text{heat}} = \rho_{o} c_{p_{o}} \gamma_{0} (max((T_{o} - T_{f})+\delta T_{sector},0))**2, @f]
//!
//! where @f$\rho_{o}@f$ is the density of ocean water, @f$c_{p_{o}}@f$ and
//! @f$T_{o}@f$ are the heat capacity and temperature of the ocean mixed
//! layer, @f$T_{f}@f$ is the freezing temperature of ocean water at the
//! shelf bottom.
class ISMIP6 : public CompleteOceanModel {
public:
  ISMIP6(IceGrid::ConstPtr g);
  virtual ~ISMIP6();

private:
  MaxTimestep max_timestep_impl(double t) const;
  void update_impl(const Geometry &geometry, double my_t, double my_dt);
  void init_impl(const Geometry &geometry);

  // outputs variables from ISMIP6 routine
  const IceModelVec2S& shelf_base_temperature_impl() const;
  const IceModelVec2S& shelf_base_mass_flux_impl() const;

  // Variables to be read from input file
  IceModelVec2T::Ptr m_shelfbtemp;
  IceModelVec2T::Ptr m_salinity_ocean;

  void compute_thermal_forcing(const IceModelVec2S &ice_thickness, const IceModelVec2S &m_shelfbtemp, const IceModelVec2S &m_salinity_ocean, std::vector<double> &thermal_forcing)
  void compute_avg_thermal_forcing(const IceModelVec2S &m_basinNumber, const IceModelVec2S &ice_shelf_mask, std::vector<double> &thermal_forcing, std::vector<double> &TF_avg); // per basin
  void melting_point_temperature(const IceModelVec2S &depth, IceModelVec2S &result) const;
  void mass_flux(std::vector<double> &thermal_forcing, std::vector<double> &TF_avg, IceModelVec2S &result) const;
};

} // end of namespace ocean
} // end of namespace pism
#endif /* _POISMIP6_H_ */
