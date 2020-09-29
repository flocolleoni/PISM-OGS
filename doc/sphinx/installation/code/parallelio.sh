#!/bin/bash

set -x
set -e
set -u

# Install NCAR ParallelIO in ~/local/parallelio
# using parallel NetCDF and PnetCDF installed in ~/local/netcdf
# and ~/local/pnetcdf. Uses ~/local/build/parallelio
# as a build directory.

netcdf_prefix=~/local/netcdf
pnetcdf_prefix=~/local/pnetcdf

url=https://github.com/NCAR/ParallelIO.git
build=~/local/build/parallelio
prefix=$HOME/local/parallelio

rm -rf ${build}
mkdir -p ${build}/build ${build}/sources

git clone --depth=1 -b master ${url} ${build}/sources

pushd ${build}/build

CC=mpicc cmake \
  -DCMAKE_C_FLAGS="-fPIC" \
  -DCMAKE_INSTALL_PREFIX=${prefix} \
  -DNetCDF_PATH=${netcdf_prefix} \
  -DPnetCDF_PATH=${pnetcdf_prefix} \
  -DPIO_ENABLE_FORTRAN=0 \
  -DPIO_ENABLE_TIMING=0 \
  ${build}/sources

make install

popd
