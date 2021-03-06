FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
        ccache \
        clang \
        python3-sphinx \
        python3-sphinxcontrib.bibtex \
        wget \
        cmake g++ git libfftw3-dev libgsl-dev libnetcdf-dev libudunits2-dev netcdf-bin petsc-dev  cmake-curses-gui libpnetcdf-dev libproj-dev  nco  python3-dev python3-netcdf4 python3-nose python3-numpy python3-petsc4py python3-pyproj python3-scipy swig

RUN useradd --create-home --system --shell=/bin/false builder && usermod --lock builder
USER builder

# Install parallel HDF5, NetCDF, PnetCDF, and ParallelIO by building them from sources.
#
# Uses wget installed above.
#
# This step uses scripts that are used to describe how to install these libraries in the
# manual. Re-using them here makes it easier to keep this part of the manual up to date.

COPY hdf5.sh /tmp/
COPY netcdf.sh /tmp/
COPY pnetcdf.sh /tmp/
COPY parallelio.sh /tmp/

RUN cd /tmp &&\
        ./hdf5.sh && \
        ./netcdf.sh && \
        ./pnetcdf.sh && \
        ./parallelio.sh && \
        rm -rf ~/local/build

# Add a flag needed to use OpenMPI in a Docker container.
# See https://github.com/open-mpi/ompi/issues/4948
# Tested on Ubuntu 20.04 (LTS)
#
# Allow oversubscribing (i.e. running more MPI processes than the number of cores
# available). Run "ompi_info --all" to get the list of MCA parameters.
ENV OMPI_MCA_btl="^vader" \
    OMPI_MCA_rmaps_base_oversubscribe=yes \
    OMPI_MCA_btl_base_warn_component_unused=0
