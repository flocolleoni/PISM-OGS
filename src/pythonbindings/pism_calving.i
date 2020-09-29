%{
#include "frontretreat/calving/CalvingAtThickness.hh"
#include "frontretreat/calving/EigenCalving.hh"
#include "frontretreat/calving/FloatKill.hh"
#include "frontretreat/calving/HayhurstCalving.hh"
#include "frontretreat/calving/vonMisesCalving.hh"
%}

%shared_ptr(pism::calving::CalvingAtThickness)
%rename(CalvingAtThickness) pism::calving::CalvingAtThickness;
%include "frontretreat/calving/CalvingAtThickness.hh"

%shared_ptr(pism::calving::StressCalving)
%rename(CalvingStressCalving) pism::calving::StressCalving;
%include "frontretreat/calving/StressCalving.hh"

%shared_ptr(pism::calving::EigenCalving)
%rename(CalvingEigenCalving) pism::calving::EigenCalving;
%include "frontretreat/calving/EigenCalving.hh"

%shared_ptr(pism::calving::FloatKill)
%rename(CalvingFloatKill) pism::calving::FloatKill;
%include "frontretreat/calving/FloatKill.hh"

%shared_ptr(pism::calving::HayhurstCalving)
%rename(CalvingHayhurstCalving) pism::calving::HayhurstCalving;
%include "frontretreat/calving/HayhurstCalving.hh"

%shared_ptr(pism::calving::vonMisesCalving)
%rename(CalvingvonMisesCalving) pism::calving::vonMisesCalving;
%include "frontretreat/calving/vonMisesCalving.hh"
