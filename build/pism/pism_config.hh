/* Copyright (C) 2019 PISM Authors
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

/*!
 * This header contains values set during PISM's configuration process.
 */

#ifndef PISM_CONFIG_HH
#define PISM_CONFIG_HH

namespace pism {

/* Path to PISM's configuration file (/Users/flo/Recherche/MODELS/PISM/pism-1.2/share/pism/pism_config.nc) */
extern const char *config_file;

/* PISM's revision string (stable v1.2.2 committed by Constantine Khrulev on 2020-08-28 12:22:53 -0800) */
extern const char *revision;

/* Configuration flags used to build the PETSc library PISM is linked to (--with-shared-libraries --with-fc=0) */
extern const char *petsc_configure_flags;

/* petsc4py version used to build PISM's Python bindings () */
extern const char *petsc4py_version;

/* SWIG version used to build PISM's Python bindings () */
extern const char *swig_version;

/* CMake version used to build PISM (3.18.2) */
extern const char *cmake_version;

/* Equal to 1 if PISM was built with debugging sanity checks enabled, 0 otherwise. */
#define Pism_DEBUG 0

/* Equal to 1 if PISM was built with Jansson, 0 otherwise. */
#define Pism_USE_JANSSON 0

/* Equal to 1 if PISM was built with PROJ, 0 otherwise. */
#define Pism_USE_PROJ 1

/* Equal to 1 if PISM was built with parallel I/O support using NetCDF-4, 0 otherwise. */
#define Pism_USE_PARALLEL_NETCDF4 0

/* Equal to 1 if PISM was built with PNetCDF's parallel I/O support. */
#define Pism_USE_PNETCDF 1

/* Equal to 1 if PISM was built with NCAR's ParallelIO. */
#define Pism_USE_PIO 0

/* Equal to 1 if PISM's Python bindings were built, 0 otherwise. */
#define Pism_BUILD_PYTHON_BINDINGS 0

} // end of namespace pism

#endif /* PISM_CONFIG_HH */
