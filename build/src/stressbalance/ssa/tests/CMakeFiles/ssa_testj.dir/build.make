# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build

# Include any dependencies generated for this target.
include src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/depend.make

# Include the progress variables for this target.
include src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/progress.make

# Include the compile flags for this target's objects.
include src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/flags.make

src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/ssa_testj.cc.o: src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/flags.make
src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/ssa_testj.cc.o: ../src/stressbalance/ssa/tests/ssa_testj.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/ssa_testj.cc.o"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/stressbalance/ssa/tests && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ssa_testj.dir/ssa_testj.cc.o -c /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/stressbalance/ssa/tests/ssa_testj.cc

src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/ssa_testj.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ssa_testj.dir/ssa_testj.cc.i"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/stressbalance/ssa/tests && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/stressbalance/ssa/tests/ssa_testj.cc > CMakeFiles/ssa_testj.dir/ssa_testj.cc.i

src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/ssa_testj.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ssa_testj.dir/ssa_testj.cc.s"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/stressbalance/ssa/tests && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/stressbalance/ssa/tests/ssa_testj.cc -o CMakeFiles/ssa_testj.dir/ssa_testj.cc.s

# Object files for target ssa_testj
ssa_testj_OBJECTS = \
"CMakeFiles/ssa_testj.dir/ssa_testj.cc.o"

# External object files for target ssa_testj
ssa_testj_EXTERNAL_OBJECTS =

ssa_testj: src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/ssa_testj.cc.o
ssa_testj: src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/build.make
ssa_testj: src/libpism.dylib
ssa_testj: /Users/flo/Recherche/MODELS/local_lib/petsc/opt/lib/libpetsc.dylib
ssa_testj: /usr/local/lib/libudunits2.dylib
ssa_testj: /usr/local/lib/libfftw3.dylib
ssa_testj: /usr/local/lib/libgsl.dylib
ssa_testj: /usr/local/lib/libgslcblas.dylib
ssa_testj: /usr/local/lib/libnetcdf.dylib
ssa_testj: /usr/local/Cellar/hdf5/1.12.0_1/lib/libhdf5.dylib
ssa_testj: /usr/local/opt/szip/lib/libsz.dylib
ssa_testj: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/lib/libz.tbd
ssa_testj: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/lib/libdl.tbd
ssa_testj: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/lib/libm.tbd
ssa_testj: /usr/local/Cellar/hdf5/1.12.0_1/lib/libhdf5_hl.dylib
ssa_testj: /usr/local/lib/libproj.dylib
ssa_testj: /usr/local/lib/libpnetcdf.dylib
ssa_testj: src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../ssa_testj"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/stressbalance/ssa/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ssa_testj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/build: ssa_testj

.PHONY : src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/build

src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/clean:
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/stressbalance/ssa/tests && $(CMAKE_COMMAND) -P CMakeFiles/ssa_testj.dir/cmake_clean.cmake
.PHONY : src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/clean

src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/depend:
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/stressbalance/ssa/tests /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/stressbalance/ssa/tests /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/stressbalance/ssa/tests/CMakeFiles/ssa_testj.dir/depend

