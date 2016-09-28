#!/bin/csh

#----------------------------------------------------------------------------
# C shell environment setup script for Geant4 9.5.1
#
# This script will configure your environment so that any Geant4 supplied
# tools, libraries and data are available in your PATH, library paths etc.
# Data libraries will only be setup if they were installed as part of the
# Geant4 installation.
#
# Source this script to perform the setup.
#
# This script is autogenerated by CMake DO NOT EDIT
#

#----------------------------------------------------------------------------
# Locate directory of self
#
# Self locate script when sourced
set ARGS=($_)
set g4sls_sourced_dir="`dirname ${ARGS[2]}`"
set geant4_envbindir="`cd ${g4sls_sourced_dir}; pwd`"



#----------------------------------------------------------------------------
# Setup binary and library paths...
#

if ( ! ${?PATH} ) then
  setenv PATH "$geant4_envbindir"
else
  setenv PATH "$geant4_envbindir":${PATH}
endif
      

if ( ! ${?DYLD_LIBRARY_PATH} ) then
  setenv DYLD_LIBRARY_PATH "`cd $geant4_envbindir/../lib; pwd`"
else
  setenv DYLD_LIBRARY_PATH "`cd $geant4_envbindir/../lib; pwd`":${DYLD_LIBRARY_PATH}
endif
      

#----------------------------------------------------------------------------
# Resource file paths
# Data Library Paths are only set if they were installed by CMake
#
# ABLA Data not installed
# EMLOW Data not installed
# Photon Evaporation Data not installed
# NDL Data not installed
# Neutron Cross Section Data not installed
# Shell Ionization Cross Section Data not installed
# Radioactive Decay Data not installed
# RealSurface Data not installed

