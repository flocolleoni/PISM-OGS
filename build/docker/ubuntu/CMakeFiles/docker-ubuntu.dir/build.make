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

# Utility rule file for docker-ubuntu.

# Include the progress variables for this target.
include docker/ubuntu/CMakeFiles/docker-ubuntu.dir/progress.make

docker/ubuntu/CMakeFiles/docker-ubuntu:
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/docker/ubuntu && docker build -t ckhrulev/pism-ubuntu:0.1 .

docker-ubuntu: docker/ubuntu/CMakeFiles/docker-ubuntu
docker-ubuntu: docker/ubuntu/CMakeFiles/docker-ubuntu.dir/build.make

.PHONY : docker-ubuntu

# Rule to build all files generated by this target.
docker/ubuntu/CMakeFiles/docker-ubuntu.dir/build: docker-ubuntu

.PHONY : docker/ubuntu/CMakeFiles/docker-ubuntu.dir/build

docker/ubuntu/CMakeFiles/docker-ubuntu.dir/clean:
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/docker/ubuntu && $(CMAKE_COMMAND) -P CMakeFiles/docker-ubuntu.dir/cmake_clean.cmake
.PHONY : docker/ubuntu/CMakeFiles/docker-ubuntu.dir/clean

docker/ubuntu/CMakeFiles/docker-ubuntu.dir/depend:
	cd /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/docker/ubuntu /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/docker/ubuntu /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/docker/ubuntu/CMakeFiles/docker-ubuntu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : docker/ubuntu/CMakeFiles/docker-ubuntu.dir/depend

