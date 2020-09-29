/* Copyright (C) 2019, 2020 PISM Authors
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

#include "pism/util/IceGrid.hh"
#include "pism/util/Logger.hh"
#include "pism/util/iceModelVec.hh"
#include "pism/util/petscwrappers/KSP.hh"
#include "pism/util/petscwrappers/Mat.hh"

namespace pism {

class Poisson {
public:
  Poisson(IceGrid::ConstPtr grid);

  int solve(const IceModelVec2Int& mask, const IceModelVec2S& bc, double rhs,
            bool reuse_matrix = false);

  const IceModelVec2S &solution() const;
private:
  void assemble_matrix(const IceModelVec2Int &mask, Mat A);
  void assemble_rhs(double rhs,
                    const IceModelVec2Int &mask,
                    const IceModelVec2S &bc,
                    IceModelVec2S &b);

  IceGrid::ConstPtr m_grid;
  Logger::ConstPtr m_log;
  petsc::DM::Ptr m_da;         // dof=1 DA used by the KSP solver
  petsc::KSP m_KSP;
  petsc::Mat m_A;
  IceModelVec2S m_b;
  IceModelVec2S m_x;
  IceModelVec2Int m_mask;
};

} // end of namespace pism
