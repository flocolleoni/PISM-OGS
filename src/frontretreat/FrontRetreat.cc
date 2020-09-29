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
#include "FrontRetreat.hh"

#include "pism/util/iceModelVec.hh"
#include "pism/util/IceModelVec2CellType.hh"
#include "pism/util/MaxTimestep.hh"
#include "pism/util/pism_utilities.hh"
#include "pism/geometry/part_grid_threshold_thickness.hh"
#include "pism/geometry/Geometry.hh"

namespace pism {

FrontRetreat::FrontRetreat(IceGrid::ConstPtr g)
  : Component(g),
    m_tmp(m_grid, "temporary_storage", WITH_GHOSTS, 1) {

  m_tmp.set_attrs("internal", "additional mass loss at points near the front",
                  "m", "m", "", 0);

  m_cell_type.create(m_grid, "cell_type", WITH_GHOSTS, 1);
  m_cell_type.set_attrs("internal", "cell type mask", "", "", "", 0);
}

FrontRetreat::~FrontRetreat() {
  // empty
}

/*!
 * Compute the modified mask to avoid "wrapping around" of front retreat at domain
 * boundaries.
 */
void FrontRetreat::compute_modified_mask(const IceModelVec2CellType &input,
                                         IceModelVec2CellType &output) const {

  IceModelVec::AccessList list{&input, &output};

  const int Mx = m_grid->Mx();
  const int My = m_grid->My();

  ParallelSection loop(m_grid->com);
  try {
    for (PointsWithGhosts p(*m_grid); p; p.next()) {
      const int i = p.i(), j = p.j();

      if (i < 0 or i >= Mx or j < 0 or j >= My) {
        output(i, j) = MASK_ICE_FREE_OCEAN;
      } else {
        output(i, j) = input(i, j);
      }
    }
  } catch (...) {
    loop.failed();
  }
  loop.check();
}

/*!
 * Compute the maximum time step length provided a horizontal retreat rate.
 */
MaxTimestep FrontRetreat::max_timestep(const IceModelVec2CellType &cell_type,
                                       const IceModelVec2Int &bc_mask,
                                       const IceModelVec2S &retreat_rate) const {

  IceGrid::ConstPtr grid = retreat_rate.grid();
  units::System::Ptr sys = grid->ctx()->unit_system();

  using units::convert;

  // About 9 hours which corresponds to 10000 km year-1 on a 10 km grid
  double dt_min = convert(sys, 0.001, "years", "seconds");

  double
    retreat_rate_max  = 0.0,
    retreat_rate_mean = 0.0;
  int N_cells = 0;

  IceModelVec::AccessList list{&cell_type, &bc_mask, &retreat_rate};

  for (Points pt(*grid); pt; pt.next()) {
    const int i = pt.i(), j = pt.j();

    if (cell_type.ice_free_ocean(i, j) and
        cell_type.next_to_ice(i, j) and
        bc_mask(i, j) < 0.5) {
      // NB: this condition has to match the one in update_geometry()

      const double C = retreat_rate(i, j);

      N_cells           += 1;
      retreat_rate_mean += C;
      retreat_rate_max   = std::max(C, retreat_rate_max);
    }
  }

  N_cells           = GlobalSum(grid->com, N_cells);
  retreat_rate_mean = GlobalSum(grid->com, retreat_rate_mean);
  retreat_rate_max  = GlobalMax(grid->com, retreat_rate_max);

  if (N_cells > 0.0) {
    retreat_rate_mean /= N_cells;
  } else {
    retreat_rate_mean = 0.0;
  }

  double denom = retreat_rate_max / grid->dx();
  const double epsilon = convert(sys, 0.001 / (grid->dx() + grid->dy()), "seconds", "years");

  double dt = 1.0 / (denom + epsilon);

  m_log->message(3,
                 "  frontal retreat: maximum rate = %.2f m/year gives dt=%.5f years\n"
                 "                   mean rate    = %.2f m/year over %d cells\n",
                 convert(m_sys, retreat_rate_max, "m second-1", "m year-1"),
                 convert(m_sys, dt, "seconds", "years"),
                 convert(m_sys, retreat_rate_mean, "m second-1", "m year-1"),
                 N_cells);

  return MaxTimestep(std::max(dt, dt_min), "front_retreat");
}

/*!
 * Update ice geometry by applying a horizontal retreat rate.
 *
 * This code applies a horizontal retreat rate at "partially-filled" cells that are next
 * to icy cells.
 *
 * Models providing the "retreat rate" should set this field to zero in areas where a
 * particular parameterization does not apply. (For example: some calving models apply at
 * shelf calving fronts, others may apply at grounded termini but not at ice shelves,
 * etc).
 */
void FrontRetreat::update_geometry(double dt,
                                   const Geometry &geometry,
                                   const IceModelVec2Int &bc_mask,
                                   const IceModelVec2S &retreat_rate,
                                   IceModelVec2S &Href,
                                   IceModelVec2S &ice_thickness) {

  const IceModelVec2S &bed = geometry.bed_elevation;
  const IceModelVec2S &sea_level = geometry.sea_level_elevation;
  const IceModelVec2S &surface_elevation = geometry.ice_surface_elevation;

  if (m_config->get_flag("geometry.front_retreat.wrap_around")) {
    m_cell_type.copy_from(geometry.cell_type);
  } else {
    // compute the modified mask needed to prevent front retreat from "wrapping around"
    // the computational domain
    compute_modified_mask(geometry.cell_type, m_cell_type);
  }

  const double dx = m_grid->dx();

  m_tmp.set(0.0);

  IceModelVec::AccessList list{&ice_thickness, &bc_mask,
      &bed, &sea_level, &m_cell_type, &Href, &m_tmp, &retreat_rate,
      &surface_elevation};

  // Prepare to loop over neighbors: directions
  const Direction dirs[] = {North, East, South, West};

  // Step 1: Apply the computed horizontal retreat rate:
  for (Points pt(*m_grid); pt; pt.next()) {
    const int i = pt.i(), j = pt.j();

    // apply retreat rate at the margin (i.e. to partially-filled cells) only
    if (m_cell_type.ice_free_ocean(i, j) and
        m_cell_type.next_to_ice(i, j) and
        bc_mask(i, j) < 0.5) {
      // NB: this condition has to match the one in max_timestep()

      const double
        rate     = retreat_rate(i, j),
        Href_old = Href(i, j);

      // Compute the number of floating neighbors and the neighbor-averaged ice thickness:
      double H_threshold = part_grid_threshold_thickness(m_cell_type.int_star(i, j),
                                                         ice_thickness.star(i, j),
                                                         surface_elevation.star(i, j),
                                                         bed(i, j));

      // Calculate mass loss with respect to the associated ice thickness and the grid size:
      const double Href_change = -dt * rate * H_threshold / dx; // in m

      if (Href_old + Href_change >= 0.0) {
        // Href is high enough to absorb the mass loss
        Href(i, j) = Href_old + Href_change;
      } else {
        Href(i, j) = 0.0;
        // Href + Href_change is negative: need to distribute mass loss to neighboring points

        // Find the number of neighbors to distribute to.
        //
        // We consider floating cells and grounded cells with the base below sea level. In other
        // words, additional mass losses are distributed to shelf calving fronts and grounded marine
        // termini.
        int N = 0;
        {
          auto
            M  = m_cell_type.int_star(i, j),
            BC = bc_mask.int_star(i, j);

          auto
            b  = bed.star(i, j),
            sl = sea_level.star(i, j);

          for (int n = 0; n < 4; ++n) {
            Direction direction = dirs[n];
            int m = M[direction];
            int bc = BC[direction];

            // note: this is where the modified cell type mask is used to prevent
            // wrap-around
            if (bc == 0 and     // distribute to regular (*not* Dirichlet B.C.) neighbors only
                (mask::floating_ice(m) or
                 (mask::grounded_ice(m) and b[direction] < sl[direction]))) {
              N += 1;
            }
          }
        }

        if (N > 0) {
          m_tmp(i, j) = (Href_old + Href_change) / (double)N;
        } else {
          // No shelf calving front of grounded terminus to distribute to: retreat stops here.
          m_tmp(i, j) = 0.0;
        }
      }

    } // end of "if ice free ocean next to ice and not a BC location "
  }   // end of loop over grid points

  // Step 2: update ice thickness and Href in neighboring cells if we need to propagate mass losses.
  m_tmp.update_ghosts();

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    // Note: this condition has to match the one in step 1 above.
    if (bc_mask.as_int(i, j) == 0 and
        (m_cell_type.floating_ice(i, j) or
         (m_cell_type.grounded_ice(i, j) and bed(i, j) < sea_level(i, j)))) {

      const double delta_H = (m_tmp(i + 1, j) + m_tmp(i - 1, j) +
                              m_tmp(i, j + 1) + m_tmp(i, j - 1));

      if (delta_H < 0.0) {
        Href(i, j) = ice_thickness(i, j) + delta_H; // in m
        ice_thickness(i, j) = 0.0;
      }

      // Stop retreat if the current cell does not have enough ice to absorb the loss.
      if (Href(i, j) < 0.0) {
        Href(i, j) = 0.0;
      }
    }
  }
}

} // end of namespace pism
