# Install script for directory: /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/flo/Recherche/MODELS/PISM/pism-1.2")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/pism" TYPE FILE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/pism/pism_config.hh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/libpism.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpism.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/pismr")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismr")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/pisms")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pisms")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/pismv")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pismv")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pism" TYPE FILE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/pism_config.nc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/btutest")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/btutest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/btutest")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/btutest")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/btutest")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/btutest")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/btutest")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/pism" TYPE DIRECTORY MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/" FILES_MATCHING REGEX "/[^/]*\\.hh$" REGEX "/[^/]*\\.h$" REGEX "/external$" EXCLUDE REGEX "/pythonbindings$" EXCLUDE REGEX "/doc$" EXCLUDE REGEX "/figs$" EXCLUDE REGEX "/ssa\\/tests$" EXCLUDE REGEX "/verification\\/tests\\/fortran$" EXCLUDE REGEX "/rheology\\/approximate$" EXCLUDE REGEX "/tracer$" EXCLUDE)
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/coupler/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/earth/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/external/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/frontretreat/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/hydrology/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/inverse/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/regional/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/rheology/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/stressbalance/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/util/cmake_install.cmake")
  include("/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src/verification/cmake_install.cmake")

endif()

