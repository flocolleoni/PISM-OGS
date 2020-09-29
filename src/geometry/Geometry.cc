/* Copyright (C) 2017, 2018, 2019 PISM Authors
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

#include "Geometry.hh"

#include "pism/util/iceModelVec.hh"
#include "pism/util/IceModelVec2CellType.hh"
#include "pism/util/Mask.hh"
#include "pism/util/pism_utilities.hh"
#include "pism/geometry/grounded_cell_fraction.hh"

namespace pism {

Geometry::Geometry(IceGrid::ConstPtr grid)
  // FIXME: ideally these fields should be "global", i.e. without ghosts.
  // (However this may increase communication costs...)
  : m_stencil_width(grid->ctx()->config()->get_number("grid.max_stencil_width")),
    latitude(grid, "lat", WITHOUT_GHOSTS),
    longitude(grid, "lon", WITHOUT_GHOSTS),
    bed_elevation(grid, "topg", WITH_GHOSTS, m_stencil_width),
    sea_level_elevation(grid, "sea_level", WITH_GHOSTS),
    ice_thickness(grid, "thk", WITH_GHOSTS, m_stencil_width),
    ice_area_specific_volume(grid, "ice_area_specific_volume", WITH_GHOSTS),
    cell_type(grid, "mask", WITH_GHOSTS, m_stencil_width),
    cell_grounded_fraction(grid, "cell_grounded_fraction", WITHOUT_GHOSTS),
    ice_surface_elevation(grid, "usurf", WITH_GHOSTS, m_stencil_width) {

  latitude.set_attrs("mapping", "latitude", "degree_north", "degree_north", "latitude", 0);
  latitude.set_time_independent(true);
  latitude.metadata().set_string("grid_mapping", "");
  latitude.metadata().set_numbers("valid_range", {-90.0, 90.0});

  longitude.set_attrs("mapping", "longitude", "degree_east", "degree_east", "longitude", 0);
  longitude.set_time_independent(true);
  longitude.metadata().set_string("grid_mapping", "");
  longitude.metadata().set_numbers("valid_range", {-180.0, 180.0});

  bed_elevation.set_attrs("model_state", "bedrock surface elevation",
                          "m", "m", "bedrock_altitude", 0);

  sea_level_elevation.set_attrs("model_state",
                                "sea level elevation above reference ellipsoid", "meters", "meters",
                                "sea_surface_height_above_reference_ellipsoid", 0);

  ice_thickness.set_attrs("model_state", "land ice thickness",
                          "m", "m", "land_ice_thickness", 0);
  ice_thickness.metadata().set_number("valid_min", 0.0);

  ice_area_specific_volume.set_attrs("model_state",
                                     "ice-volume-per-area in partially-filled grid cells",
                                     "m3/m2", "m3/m2", "", 0);
  ice_area_specific_volume.metadata().set_string("comment",
                                                 "this variable represents the amount of ice "
                                                 "in a partially-filled cell and not "
                                                 "the corresponding geometry, so thinking "
                                                 "about it as 'thickness' is not helpful");

  cell_type.set_attrs("diagnostic", "ice-type (ice-free/grounded/floating/ocean) integer mask",
                      "", "", "", 0);
  cell_type.metadata().set_numbers("flag_values", {MASK_ICE_FREE_BEDROCK, MASK_GROUNDED,
                                                   MASK_FLOATING, MASK_ICE_FREE_OCEAN});
  cell_type.metadata().set_string("flag_meanings",
                                  "ice_free_bedrock grounded_ice floating_ice ice_free_ocean");
  cell_type.metadata().set_output_type(PISM_INT);

  cell_grounded_fraction.set_attrs("internal",
                                   "fractional grounded/floating mask (floating=0, grounded=1)",
                                   "", "", "", 0);

  ice_surface_elevation.set_attrs("diagnostic", "ice upper surface elevation",
                                  "m", "m", "surface_altitude", 0);

  // make sure all the fields are initialized
  latitude.set(0.0);
  longitude.set(0.0);
  bed_elevation.set(0.0);
  sea_level_elevation.set(0.0);
  ice_thickness.set(0.0);
  ice_area_specific_volume.set(0.0);
  ensure_consistency(0.0);
}

void check_minimum_ice_thickness(const IceModelVec2S &ice_thickness) {
  IceGrid::ConstPtr grid = ice_thickness.grid();

  IceModelVec::AccessList list(ice_thickness);

  ParallelSection loop(grid->com);
  try {
    for (Points p(*grid); p; p.next()) {
      const int i = p.i(), j = p.j();

      if (ice_thickness(i, j) < 0.0) {
        throw RuntimeError::formatted(PISM_ERROR_LOCATION,
                                      "H = %e (negative) at point i=%d, j=%d",
                                      ice_thickness(i, j), i, j);
      }
    }
  } catch (...) {
    loop.failed();
  }
  loop.check();
}

void Geometry::ensure_consistency(double ice_free_thickness_threshold) {
  IceGrid::ConstPtr grid = ice_thickness.grid();
  Config::ConstPtr config = grid->ctx()->config();

  check_minimum_ice_thickness(ice_thickness);

  IceModelVec::AccessList list{&sea_level_elevation, &bed_elevation,
      &ice_thickness, &ice_area_specific_volume,
      &cell_type, &ice_surface_elevation};

  // first ensure that ice_area_specific_volume is 0 if ice_thickness > 0.
  {
    ParallelSection loop(grid->com);
    try {
      for (Points p(*grid); p; p.next()) {
        const int i = p.i(), j = p.j();

        if (ice_thickness(i, j) > 0.0 and ice_area_specific_volume(i, j) > 0.0) {
          ice_thickness(i, j) += ice_area_specific_volume(i, j);
          ice_area_specific_volume(i, j) = 0.0;
        }
      }
    } catch (...) {
      loop.failed();
    }
    loop.check();
  }

  // compute cell type and surface elevation
  {
    GeometryCalculator gc(*config);
    gc.set_icefree_thickness(ice_free_thickness_threshold);

    ParallelSection loop(grid->com);
    try {
      for (Points p(*grid); p; p.next()) {
        const int i = p.i(), j = p.j();

        int mask = 0;
        gc.compute(sea_level_elevation(i, j), bed_elevation(i, j), ice_thickness(i, j),
                   &mask, &ice_surface_elevation(i, j));
        cell_type(i, j) = mask;
      }
    } catch (...) {
      loop.failed();
    }
    loop.check();
  }

  ice_thickness.update_ghosts();
  ice_area_specific_volume.update_ghosts();
  cell_type.update_ghosts();
  ice_surface_elevation.update_ghosts();

  const double
    ice_density = config->get_number("constants.ice.density"),
    ocean_density = config->get_number("constants.sea_water.density");

  compute_grounded_cell_fraction(ice_density,
                                 ocean_density,
                                 sea_level_elevation,
                                 ice_thickness,
                                 bed_elevation,
                                 cell_grounded_fraction);
}

/*! Compute the elevation of the bottom surface of the ice.
 */
void ice_bottom_surface(const Geometry &geometry, IceModelVec2S &result) {

  auto grid = result.grid();
  auto config = grid->ctx()->config();

  double
    ice_density   = config->get_number("constants.ice.density"),
    water_density = config->get_number("constants.sea_water.density"),
    alpha         = ice_density / water_density;

  const IceModelVec2S &ice_thickness = geometry.ice_thickness;
  const IceModelVec2S &bed_elevation = geometry.bed_elevation;
  const IceModelVec2S &sea_level     = geometry.sea_level_elevation;

  IceModelVec::AccessList list{&ice_thickness, &bed_elevation, &sea_level, &result};

  ParallelSection loop(grid->com);
  try {
    for (Points p(*grid); p; p.next()) {
      const int i = p.i(), j = p.j();

      double
        b_grounded = bed_elevation(i, j),
        b_floating = sea_level(i, j) - alpha * ice_thickness(i, j);

      result(i, j) = std::max(b_grounded, b_floating);
    }
  } catch (...) {
    loop.failed();
  }
  loop.check();

  result.update_ghosts();
}

//! Computes the ice volume, in m^3.
double ice_volume(const Geometry &geometry, double thickness_threshold) {
  auto grid = geometry.ice_thickness.grid();
  auto config = grid->ctx()->config();

  IceModelVec::AccessList list{&geometry.ice_thickness};

  double volume = 0.0;

  auto cell_area = grid->cell_area();

  {
    for (Points p(*grid); p; p.next()) {
      const int i = p.i(), j = p.j();

      if (geometry.ice_thickness(i,j) >= thickness_threshold) {
        volume += geometry.ice_thickness(i,j) * cell_area;
      }
    }
  }

  // Add the volume of the ice in Href:
  if (config->get_flag("geometry.part_grid.enabled")) {
    list.add(geometry.ice_area_specific_volume);
    for (Points p(*grid); p; p.next()) {
      const int i = p.i(), j = p.j();

      volume += geometry.ice_area_specific_volume(i,j) * cell_area;
    }
  }

  return GlobalSum(grid->com, volume);
}

double ice_volume_not_displacing_seawater(const Geometry &geometry,
                                          double thickness_threshold) {
  auto grid = geometry.ice_thickness.grid();
  auto config = grid->ctx()->config();

  const double
    sea_water_density = config->get_number("constants.sea_water.density"),
    ice_density       = config->get_number("constants.ice.density"),
    cell_area         = grid->cell_area();

  IceModelVec::AccessList list{&geometry.cell_type, &geometry.ice_thickness,
      &geometry.bed_elevation, &geometry.sea_level_elevation};

  double volume = 0.0;

  for (Points p(*grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    const double
      bed       = geometry.bed_elevation(i, j),
      thickness = geometry.ice_thickness(i, j),
      sea_level = geometry.sea_level_elevation(i, j);

    if (geometry.cell_type.grounded(i, j) and thickness > thickness_threshold) {
      const double cell_ice_volume = thickness * cell_area;
      if (bed > sea_level) {
        volume += cell_ice_volume;
      } else {
        const double max_floating_volume = (sea_level - bed) * cell_area * (sea_water_density / ice_density);
        volume += cell_ice_volume - max_floating_volume;
      }
    }
  } // end of the loop over grid points

  return GlobalSum(grid->com, volume);
}

//! Computes ice area, in m^2.
double ice_area(const Geometry &geometry, double thickness_threshold) {
  auto grid = geometry.ice_thickness.grid();

  double area = 0.0;

  auto cell_area = grid->cell_area();

  IceModelVec::AccessList list{&geometry.ice_thickness};
  for (Points p(*grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    if (geometry.ice_thickness(i, j) >= thickness_threshold) {
      area += cell_area;
    }
  }

  return GlobalSum(grid->com, area);
}

//! Computes grounded ice area, in m^2.
double ice_area_grounded(const Geometry &geometry, double thickness_threshold) {
  auto grid = geometry.ice_thickness.grid();

  double area = 0.0;

  auto cell_area = grid->cell_area();

  IceModelVec::AccessList list{&geometry.cell_type, &geometry.ice_thickness};
  for (Points p(*grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    if (geometry.cell_type.grounded(i, j) and
        geometry.ice_thickness(i, j) >= thickness_threshold) {
      area += cell_area;
    }
  }

  return GlobalSum(grid->com, area);
}

//! Computes floating ice area, in m^2.
double ice_area_floating(const Geometry &geometry, double thickness_threshold) {
  auto grid = geometry.ice_thickness.grid();

  double area = 0.0;

  auto cell_area = grid->cell_area();

  IceModelVec::AccessList list{&geometry.cell_type, &geometry.ice_thickness};
  for (Points p(*grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    if (geometry.cell_type.ocean(i, j) and
        geometry.ice_thickness(i, j) >= thickness_threshold) {
      area += cell_area;
    }
  }

  return GlobalSum(grid->com, area);
}


//! Computes the sea level rise that would result if all the ice were melted.
double sea_level_rise_potential(const Geometry &geometry, double thickness_threshold) {
  auto config = geometry.ice_thickness.grid()->ctx()->config();

  const double
    water_density = config->get_number("constants.fresh_water.density"),
    ice_density   = config->get_number("constants.ice.density"),
    ocean_area    = config->get_number("constants.global_ocean_area");

  const double
    volume                  = ice_volume_not_displacing_seawater(geometry,
                                                                 thickness_threshold),
    additional_water_volume = (ice_density / water_density) * volume,
    sea_level_change        = additional_water_volume / ocean_area;

  return sea_level_change;
}


/*!
 * @brief Set no_model_mask variable to have value 1 in strip of width 'strip' m around
 * edge of computational domain, and value 0 otherwise.
 */
void set_no_model_strip(const IceGrid &grid, double width, IceModelVec2Int &result) {

  if (width <= 0.0) {
    return;
  }

  IceModelVec::AccessList list(result);

  for (Points p(grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    if (in_null_strip(grid, i, j, width)) {
      result(i, j) = 1;
    } else {
      result(i, j) = 0;
    }
  }

  result.update_ghosts();
}

} // end of namespace pism
