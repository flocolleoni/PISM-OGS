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

#ifndef _PSISMIP6_H_
#define _PSISMIP6_H_

#include "pism/coupler/SurfaceModel.hh"
#include "pism/util/iceModelVec2T.hh"

namespace pism {
namespace surface {

class ISMIP6 : public SurfaceModel {
public:
  ISMIP6(IceGrid::ConstPtr g, std::shared_ptr<atmosphere::AtmosphereModel> input);
  virtual ~ISMIP6();
protected:
  void init_impl(const Geometry &geometry);
  void update_impl(const Geometry &geometry, double t, double dt);

  const IceModelVec2S &temperature_impl() const;
  const IceModelVec2S &mass_flux_impl() const;

  const IceModelVec2S& accumulation_impl() const;
  const IceModelVec2S& melt_impl() const;
  const IceModelVec2S& runoff_impl() const;
  MaxTimestep max_timestep_impl(double t) const;
protected:
  // time-dependent inputs
  IceModelVec2T::Ptr m_mass_flux_anomaly;
  IceModelVec2T::Ptr m_temperature_anomaly;
  IceModelVec2T::Ptr m_mass_flux_gradient;
  IceModelVec2T::Ptr m_temperature_gradient;

  // time-independent inputs
  IceModelVec2S m_mass_flux_reference;
  IceModelVec2S m_temperature_reference;
  IceModelVec2S m_surface_reference;

  // outputs; stored as shared_ptr to be able to use SurfaceModel::allocate_xxx()
  IceModelVec2S::Ptr m_mass_flux;
  IceModelVec2S::Ptr m_temperature;

};

} // end of namespace surface
} // end of namespace pism

#endif /* _PSISMIP6_H_ */
