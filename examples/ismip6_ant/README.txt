!---------------------------------------------------------------------------------
! Test for ISMIP6 oceanic parameterisation 2D from Jourdain et al. (2020).
!
! Those scripts set up a short bootstrapping run and a short no-mass run to
! test the ISMIP6 oceanic models for Antarctica.
!
!---------------------------------------------------------------------------------

User needs to adapt the script to their own environment:
- set_environment.sh: local user environment
- run_paleo.sh: location of input files and PISM configuration file need to be adjusted as well
- run_pismr.sh: location of directories to be modified

ISMIP6 oceanic model (both local and non-local are implemented) is:
-------------------------------------------------------------------
- ocean.ismip6_2d

Other options of ismip6_2d can be set in the pism_config.cdl file or directly in set_physics.sh


Input files:
---------------
- atmospheric and topographic conditions: bedmap2_martos_MAR_monthly_pism30km.nc
- oceanic temperature, salinity, deltaT and basins: from ISMIP6 Jourdain et al. Python package. 3D T and S vertically averaged over depth**

The oceanic files can be used by both ISMIP6 methods.
For the local method: drainage basins are not necessary and thus do not need to be set up.
For both methods: deltaT file is optional, if not set in the set_physics.sh, this correction is seto to default value = 0.



RUNNING:
---------------

 sh run_pismr.sh

 to run all the scripts.


** Note that those vertically averaged T,S as well as the deltaT file have not been recalibrated. Jourdain et al. (2020) provide a package to calibrate deltaT and gamma0 to match Rignot et al. basal melt rates. Here, for the seek of the example, we just provide a vertically averaged file of T,S and an ad-hoc deltaT file. The user might thus be carefull and recalibrate T properly