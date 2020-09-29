# CMake generated Testfile for 
# Source directory: /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression
# Build directory: /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/test/regression
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pism_testing_tools:test_regression_tools.py "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_regression_tools.py" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(pism_testing_tools:test_regression_tools.py PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;39;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(pismr_exact_restartability_SIA_only:test_01.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_01.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(pismr_exact_restartability_SIA_only:test_01.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;41;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(pismv_processor_independence:test_02.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_02.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(pismv_processor_independence:test_02.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;43;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(pismr_zero_length_run:test_03.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_03.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(pismr_zero_length_run:test_03.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;45;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(pismr_regridding_during_bootstrapping:test_04.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_04.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(pismr_regridding_during_bootstrapping:test_04.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;47;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(pismr_bootstrap_variable_order:test_05.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_05.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(pismr_bootstrap_variable_order:test_05.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;49;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(pismr_bootstrap_variable_ranges:test_06.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_06.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(pismr_bootstrap_variable_ranges:test_06.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;51;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(regridding:bootstrap_vs_regrid_file:test_07.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_07.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(regridding:bootstrap_vs_regrid_file:test_07.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;53;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(regridding:vertical_direction:test_08.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_08.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(regridding:vertical_direction:test_08.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;55;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(regridding:variable_order:test_09.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_09.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(regridding:variable_order:test_09.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;57;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(regridding:processor_independence:test_10.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_10.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(regridding:processor_independence:test_10.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;59;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(regridding:no_enthalpy:test_32.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_32.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(regridding:no_enthalpy:test_32.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;61;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(SIA_mass_conservation:test_12.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_12.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(SIA_mass_conservation:test_12.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;63;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(temperature_continuity_base_polythermal:temp_continuity.py "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/temp_continuity.py" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(temperature_continuity_base_polythermal:temp_continuity.py PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;65;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(enthalpy_symmetry_near_base:test_13.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_13.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(enthalpy_symmetry_near_base:test_13.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;67;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_C:test_15.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_15.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_C:test_15.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;69;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_L:test_16.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_16.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_L:test_16.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;71;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_G:test_17.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_17.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_G:test_17.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;73;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_K:test_18.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_18.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_K:test_18.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;75;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(restart:i_vs_bootstrap_and_regrid_file:test_23.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_23.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(restart:i_vs_bootstrap_and_regrid_file:test_23.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;77;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(runtime_viewers:test_27.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_27.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(runtime_viewers:test_27.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;79;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(bootstrapping_incomplete_input:test_28.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_28.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(bootstrapping_incomplete_input:test_28.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;81;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(distributed_hydrology:test_29.py "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_29.py" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(distributed_hydrology:test_29.py PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;83;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(initialization_without_enthalpy:test_31.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_31.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(initialization_without_enthalpy:test_31.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;85;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(vertical_grid_expansion:vertical_grid_expansion.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/vertical_grid_expansion.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(vertical_grid_expansion:vertical_grid_expansion.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;87;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(bed_deformation:LC:exact_restartability:beddef_lc_restart.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/beddef_lc_restart.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(bed_deformation:LC:exact_restartability:beddef_lc_restart.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;89;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(epsg_code_processing:test_epsg_processing.py "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/test_epsg_processing.py" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(epsg_code_processing:test_epsg_processing.py PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;92;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:PISMBedThermalUnit_test_K:btu_regression.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/btu_regression.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:PISMBedThermalUnit_test_K:btu_regression.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;100;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_V_SSAFD_CFBC:ssa/ssa_test_cfbc_fd.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/ssa/ssa_test_cfbc_fd.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_V_SSAFD_CFBC:ssa/ssa_test_cfbc_fd.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;102;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_V_SSAFEM_CFBC:ssa/ssa_test_cfbc_fem.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/ssa/ssa_test_cfbc_fem.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_V_SSAFEM_CFBC:ssa/ssa_test_cfbc_fem.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;104;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_I_SSAFD:ssa/ssa_testi_fd.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/ssa/ssa_testi_fd.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_I_SSAFD:ssa/ssa_testi_fd.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;106;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_I_SSAFEM:ssa/ssa_testi_fem.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/ssa/ssa_testi_fem.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_I_SSAFEM:ssa/ssa_testi_fem.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;108;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_J_SSAFD:ssa/ssa_testj_fd.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/ssa/ssa_testj_fd.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_J_SSAFD:ssa/ssa_testj_fd.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;110;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:test_J_SSAFEM:ssa/ssa_testj_fem.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/ssa/ssa_testj_fem.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:test_J_SSAFEM:ssa/ssa_testj_fem.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;112;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:SSAFEM_linear_flow:ssa/ssafem_test_linear.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/ssa/ssafem_test_linear.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:SSAFEM_linear_flow:ssa/ssafem_test_linear.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;114;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
add_test(Verification:SSAFEM_plug_flow:ssa/ssafem_test_plug.sh "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/ssa/ssafem_test_plug.sh" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build" "/usr/local/bin/mpiexec" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources")
set_tests_properties(Verification:SSAFEM_plug_flow:ssa/ssafem_test_plug.sh PROPERTIES  _BACKTRACE_TRIPLES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;26;add_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;116;pism_test;/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/test/regression/CMakeLists.txt;0;")
