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
include src/CMakeFiles/pisms.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/pisms.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/pisms.dir/flags.make

src/CMakeFiles/pisms.dir/pisms.cc.o: src/CMakeFiles/pisms.dir/flags.make
src/CMakeFiles/pisms.dir/pisms.cc.o: ../src/pisms.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/pisms.dir/pisms.cc.o"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pisms.dir/pisms.cc.o -c /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/pisms.cc

src/CMakeFiles/pisms.dir/pisms.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pisms.dir/pisms.cc.i"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/pisms.cc > CMakeFiles/pisms.dir/pisms.cc.i

src/CMakeFiles/pisms.dir/pisms.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pisms.dir/pisms.cc.s"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/pisms.cc -o CMakeFiles/pisms.dir/pisms.cc.s

src/CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.o: src/CMakeFiles/pisms.dir/flags.make
src/CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.o: ../src/icemodel/IceEISModel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.o"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.o -c /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/icemodel/IceEISModel.cc

src/CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.i"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/icemodel/IceEISModel.cc > CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.i

src/CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.s"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/icemodel/IceEISModel.cc -o CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.s

# Object files for target pisms
pisms_OBJECTS = \
"CMakeFiles/pisms.dir/pisms.cc.o" \
"CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.o"

# External object files for target pisms
pisms_EXTERNAL_OBJECTS =

pisms: src/CMakeFiles/pisms.dir/pisms.cc.o
pisms: src/CMakeFiles/pisms.dir/icemodel/IceEISModel.cc.o
pisms: src/CMakeFiles/pisms.dir/build.make
pisms: src/libpism.dylib
pisms: /Users/flo/Recherche/MODELS/local_lib/petsc/opt/lib/libpetsc.dylib
pisms: /usr/local/lib/libudunits2.dylib
pisms: /usr/local/lib/libfftw3.dylib
pisms: /usr/local/lib/libgsl.dylib
pisms: /usr/local/lib/libgslcblas.dylib
pisms: /usr/local/lib/libnetcdf.dylib
pisms: /usr/local/Cellar/hdf5/1.12.0_1/lib/libhdf5.dylib
pisms: /usr/local/opt/szip/lib/libsz.dylib
pisms: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/lib/libz.tbd
pisms: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/lib/libdl.tbd
pisms: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/lib/libm.tbd
pisms: /usr/local/Cellar/hdf5/1.12.0_1/lib/libhdf5_hl.dylib
pisms: /usr/local/lib/libproj.dylib
pisms: /usr/local/lib/libpnetcdf.dylib
pisms: src/CMakeFiles/pisms.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../pisms"
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pisms.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/pisms.dir/build: pisms

.PHONY : src/CMakeFiles/pisms.dir/build

src/CMakeFiles/pisms.dir/clean:
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src && $(CMAKE_COMMAND) -P CMakeFiles/pisms.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/pisms.dir/clean

src/CMakeFiles/pisms.dir/depend:
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/CMakeFiles/pisms.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/pisms.dir/depend

