# Install script for directory: /Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/src/stressbalance/ssa/tests

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/ssa_testi")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testi" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testi")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testi")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testi")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testi")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testi")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/ssa_testj")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testj" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testj")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testj")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testj")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testj")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_testj")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/ssa_test_const")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_const" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_const")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_const")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_const")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_const")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_const")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/ssa_test_linear")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_linear" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_linear")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_linear")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_linear")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_linear")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_linear")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/ssa_test_plug")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_plug" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_plug")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_plug")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_plug")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_plug")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_plug")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE MESSAGE_LAZY FILES "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/ssa_test_cfbc")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_cfbc" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_cfbc")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -change "@rpath/libpism.dylib" "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib/libpism.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_cfbc")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/sources/build/src"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_cfbc")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/flo/Recherche/MODELS/PISM/pism-1.2/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_cfbc")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ssa_test_cfbc")
    endif()
  endif()
endif()

