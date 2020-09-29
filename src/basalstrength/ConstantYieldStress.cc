// Copyright (C) 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019 Constantine Khroulev
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

#include "ConstantYieldStress.hh"

#include "pism/util/pism_options.hh"
#include "pism/util/ConfigInterface.hh"
#include "pism/util/IceGrid.hh"
#include "pism/util/MaxTimestep.hh"
#include "pism/util/pism_utilities.hh"

namespace pism {

ConstantYieldStress::ConstantYieldStress(IceGrid::ConstPtr grid)
  : YieldStress(grid) {

  m_name = "constant yield stress model";
}

ConstantYieldStress::~ConstantYieldStress() {
  // empty
}

void ConstantYieldStress::restart_impl(const File &input_file, int record) {
  m_basal_yield_stress.read(input_file, record);

  regrid(name(), m_basal_yield_stress);
}

void ConstantYieldStress::bootstrap_impl(const File &input_file,
                                         const YieldStressInputs &inputs) {
  (void) inputs;

  double tauc = m_config->get_number("basal_yield_stress.constant.value");
  m_basal_yield_stress.regrid(input_file, OPTIONAL, tauc);

  regrid(name(), m_basal_yield_stress);
}

void ConstantYieldStress::init_impl(const YieldStressInputs &inputs) {
  (void) inputs;

  double tauc = m_config->get_number("basal_yield_stress.constant.value");
  // Set the constant value.
  m_basal_yield_stress.set(tauc);

  regrid(name(), m_basal_yield_stress);
}

MaxTimestep ConstantYieldStress::max_timestep_impl(double t) const {
  (void) t;
  return MaxTimestep(name());
}

void ConstantYieldStress::update_impl(const YieldStressInputs &inputs,
                                      double t, double dt) {
  (void) inputs;
  (void) t;
  (void) dt;
  // empty
}

} // end of namespace pism
