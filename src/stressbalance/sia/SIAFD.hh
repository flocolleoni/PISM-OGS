// Copyright (C) 2004--2019 Jed Brown, Ed Bueler and Constantine Khroulev
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

#ifndef _SIAFD_H_
#define _SIAFD_H_

#include "pism/stressbalance/SSB_Modifier.hh"      // derives from SSB_Modifier

namespace pism {

class Geometry;

namespace stressbalance {

class BedSmoother;

/** Implements the shallow ice approximation stress balance.
 *
 * Inputs:
 *
 * - ice geometry (thickness, bed elevation, surface elevation, cell
 *   type mask)
 * - ice enthalpy
 * - ice age (could be used to compute the grain size)
 * - sliding velocity
 *
 * Outputs:
 *
 * - horizontal velocity (3D fields)
 * - diffusive ice flux (for use in the geometry update)
 * - maximum diffusivity (used to determine the maximum allowed time
 *   step length)
 * - volumetric strain heating
 */
class SIAFD : public SSB_Modifier
{
public:
  SIAFD(IceGrid::ConstPtr g);

  virtual ~SIAFD();

  virtual void init();

  virtual void update(const IceModelVec2V &sliding_velocity,
                      const Inputs &inputs,
                      bool full_update);

  const BedSmoother& bed_smoother() const;

  const IceModelVec2Stag& surface_gradient_x() const;
  const IceModelVec2Stag& surface_gradient_y() const;
  const IceModelVec2Stag& diffusivity() const;

protected:
  virtual DiagnosticList diagnostics_impl() const;

  virtual void compute_surface_gradient(const Inputs &inputs,
                                        IceModelVec2Stag &h_x, IceModelVec2Stag &h_y);

  virtual void surface_gradient_eta(const IceModelVec2S &ice_thickness,
                                    const IceModelVec2S &bed_elevation,
                                    IceModelVec2Stag &h_x, IceModelVec2Stag &h_y);
  virtual void surface_gradient_haseloff(const IceModelVec2S &ice_surface_elevation,
                                         const IceModelVec2CellType &cell_type,
                                         IceModelVec2Stag &h_x, IceModelVec2Stag &h_y);
  virtual void surface_gradient_mahaffy(const IceModelVec2S &ice_surface_elevation,
                                        IceModelVec2Stag &h_x, IceModelVec2Stag &h_y);

  virtual void compute_diffusivity(bool full_update,
                                   const Geometry &geometry,
                                   const IceModelVec3 *enthalpy,
                                   const IceModelVec3 *age,
                                   const IceModelVec2Stag &h_x,
                                   const IceModelVec2Stag &h_y,
                                   IceModelVec2Stag &result);

  virtual void compute_diffusive_flux(const IceModelVec2Stag &h_x, const IceModelVec2Stag &h_y,
                                      const IceModelVec2Stag &diffusivity,
                                      IceModelVec2Stag &result);

  virtual void compute_3d_horizontal_velocity(const Geometry &geometry,
                                              const IceModelVec2Stag &h_x,
                                              const IceModelVec2Stag &h_y,
                                              const IceModelVec2V &vel_input,
                                              IceModelVec3 &u_out, IceModelVec3 &v_out);

  virtual void compute_I(const Geometry &geometry);

  bool interglacial(double accumulation_time);

  const unsigned int m_stencil_width;

  //! temporary storage for eta, theta and the smoothed thickness
  IceModelVec2S m_work_2d_0;
  IceModelVec2S m_work_2d_1;
  //! temporary storage for the surface gradient and the diffusivity
  IceModelVec2Stag m_h_x, m_h_y, m_D;
  //! temporary storage for delta on the staggered grid
  IceModelVec3 m_delta_0;
  IceModelVec3 m_delta_1;
  //! temporary storage used to store I and strain_heating on the staggered grid
  IceModelVec3 m_work_3d_0;
  IceModelVec3 m_work_3d_1;

  BedSmoother *m_bed_smoother;

  // profiling
  int m_event_sia;

  // unit conversion
  double m_seconds_per_year;
  // enhancement factor-age coupling parameters
  double m_holocene_start;
  double m_eemian_start;
  double m_eemian_end;
};

} // end of namespace stressbalance
} // end of namespace pism

#endif /* _SIAFD_H_ */
