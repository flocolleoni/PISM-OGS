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

# Utility rule file for test-python.

# Include the progress variables for this target.
include CMakeFiles/test-python.dir/progress.make

CMakeFiles/test-python:
	/usr/local/Cellar/cmake/3.18.2/bin/ctest -R Python:

test-python: CMakeFiles/test-python
test-python: CMakeFiles/test-python.dir/build.make

.PHONY : test-python

# Rule to build all files generated by this target.
CMakeFiles/test-python.dir/build: test-python

.PHONY : CMakeFiles/test-python.dir/build

CMakeFiles/test-python.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test-python.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test-python.dir/clean

CMakeFiles/test-python.dir/depend:
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/CMakeFiles/test-python.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test-python.dir/depend

