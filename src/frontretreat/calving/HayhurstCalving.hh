/* Copyright (C) 2016, 2017, 2018, 2019 PISM Authors
 *
 * This file is part of PISM.
 *
 * PISM is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * PISM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PISM; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef HAYHURSTCALVING_H
#define HAYHURSTCALVING_H

#include "pism/util/Component.hh"

namespace pism {

class Geometry;

namespace calving {

class HayhurstCalving : public Component {
public:
  HayhurstCalving(IceGrid::ConstPtr grid);
  virtual ~HayhurstCalving();

  void init();

  void update(const IceModelVec2CellType &cell_type, const IceModelVec2S &ice_thickness,
              const IceModelVec2S &sea_level, const IceModelVec2S &bed_elevation);

  const IceModelVec2S &calving_rate() const;

protected:
  DiagnosticList diagnostics_impl() const;
  
protected:
  IceModelVec2S m_calving_rate;

  double m_B_tilde, m_exponent_r, m_sigma_threshold;

};

} // end of namespace calving
} // end of namespace pism

#endif /* HAYHURSTCALVING_H */
