/* Copyright (C) 2015, 2016, 2017, 2018, 2019 PISM Authors
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

#ifndef _PROJECTION_H_
#define _PROJECTION_H_

#include <string>

#include "Units.hh"
#include "VariableMetadata.hh"

namespace pism {

class File;
class IceModelVec2S;
class IceModelVec3D;

/*! @brief Convert a proj string with an EPSG code to a set of CF attributes. */
/*!
 * Fails if `proj_string` does not contain an EPSG code.
 */
VariableMetadata epsg_to_cf(units::System::Ptr system, const std::string &proj_string);

class MappingInfo {
public:
  MappingInfo(const std::string &mapping_name, units::System::Ptr unit_system);
  VariableMetadata mapping;
  std::string proj;
};

/*! @brief Check consistency of the "mapping" variable with the EPSG code in the proj string. */
/*!
 * If the consistency check fails, throws RuntimeError explaining the failure. Fails if `info.proj`
 * does not use an EPSG code.
 */
void check_consistency_epsg(const MappingInfo &info);

/*! @brief Get projection info from a file. */
MappingInfo get_projection_info(const File &input_file, const std::string &mapping_name,
                                units::System::Ptr unit_system);

void compute_longitude(const std::string &projection, IceModelVec2S &result);
void compute_latitude(const std::string &projection, IceModelVec2S &result);

void compute_lon_bounds(const std::string &projection, IceModelVec3D &result);
void compute_lat_bounds(const std::string &projection, IceModelVec3D &result);

} // end of namespace pism

#endif /* _PROJECTION_H_ */
