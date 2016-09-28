#!/bin/sh

#----------------------------------------------------------------------------
# Bourne shell environment setup script for Geant4 9.5.1
#
# This script will configure your environment to provide a setup which can
# be used to build user applications using the old Geant4 GNUmakefile build
# system, but with a CMake build or install of Geant4.
#
# This script is autogenerated by CMake DO NOT EDIT
#

#----------------------------------------------------------------------------
# Locate directory of self
#
# Self locate script when sourced
if [ "x${BASH_ARGV[0]}" = "x" ]; then
  # Not bash, so rely on sourcing from correct location
  if [ ! -f geant4make.sh ]; then
    echo 'ERROR: cd to location of geant4make script and source it there'
    return 1
  fi
  geant4make_root=$(pwd)
else
  g4sls_sourced_dir=$(dirname ${BASH_ARGV[0]})
  geant4make_root=$(cd $g4sls_sourced_dir; pwd)
fi
      

#----------------------------------------------------------------------------
# Cleanup any existing known environment variables
# NB: It won't help with resetting paths!!
#
# - Core Variables
unset  G4INSTALL
unset  G4SYSTEM
unset  G4INCLUDE
unset  G4LIB
unset  G4DEBUG

# - Library build options
unset  G4LIB_BUILD_SHARED
unset  G4LIB_BUILD_STATIC
unset  G4LIB_USE_DLL
unset  G4LIB_USE_GRANULAR

# - Optional component build
#
# - CLHEP options
unset  CLHEP_BASE_DIR
unset  CLHEP_INCLUDE_DIR
unset  CLHEP_LIB
unset  CLHEP_LIB_DIR

# - G3ToG4
unset  G4LIB_BUILD_G3TOG4
unset  G4LIB_USE_G3TOG4

# - ZLIB options
unset  G4LIB_BUILD_ZLIB
unset  G4LIB_USE_ZLIB

# - GDML Options
unset  G4LIB_BUILD_GDML
unset  G4LIB_USE_GDML
unset  XERCESCROOT

# - UI Build and Use options
# USE options only for applications.
unset  G4UI_NONE
unset  G4UI_BUILD_QT_SESSION
unset  G4UI_BUILD_WIN32_SESSION
unset  G4UI_BUILD_XAW_SESSION
unset  G4UI_BUILD_XM_SESSION

unset  G4UI_USE_TCSH
unset  G4UI_USE_WIN32
unset  G4UI_USE_XAW
unset  G4UI_USE_XM
unset  G4UI_USE_QT

#- VIS Build and Use options
# Only USE options matter for applications.
unset  G4VIS_NONE

# - Network DAWN driver
unset  G4VIS_BUILD_DAWN_DRIVER
unset  G4VIS_USE_DAWN

# - Network VRML driver
unset  G4VIS_BUILD_VRML_DRIVER
unset  G4VIS_USE_VRML

# - OpenInventor driver
unset  G4VIS_BUILD_OIWIN32_DRIVER
unset  G4VIS_USE_OIWIN32
unset  G4VIS_BUILD_OIX_DRIVER
unset  G4VIS_USE_OIX

# - OpenGL drivers
unset  G4VIS_BUILD_OPENGLQT_DRIVER
unset  G4VIS_USE_OPENGLQT

unset  G4VIS_BUILD_OPENGLWIN32_DRIVER
unset  G4VIS_USE_OPENGLWIN32

unset  G4VIS_BUILD_OPENGLXM_DRIVER
unset  G4VIS_USE_OPENGLXM

unset  G4VIS_BUILD_OPENGLX_DRIVER
unset  G4VIS_USE_OPENGLX

# - Raytracer X11
unset  G4VIS_BUILD_RAYTRACERX_DRIVER
unset  G4VIS_USE_RAYTRACERX


#----------------------------------------------------------------------------
# System description and standard install paths
#
export G4SYSTEM=Darwin-UNSUPPORTED
export G4INSTALL="$geant4make_root"
export G4INCLUDE="`cd $geant4make_root/../../../include/Geant4; pwd`"
export G4LIB="`cd $geant4make_root/../../../lib/Geant4-9.5.1; pwd`"

if test "x$DYLD_LIBRARY_PATH" = "x" ; then
  export DYLD_LIBRARY_PATH="`cd $geant4make_root/../../../lib; pwd`"
else
  export DYLD_LIBRARY_PATH="`cd $geant4make_root/../../../lib; pwd`":${DYLD_LIBRARY_PATH}
fi


#----------------------------------------------------------------------------
# User's G4WORKDIR
#

if test "x$G4WORKDIR" = "x" ; then
  export G4WORKDIR=$HOME/geant4_workdir
fi


if test "x$PATH" = "x" ; then
  export PATH=${G4WORKDIR}/bin/${G4SYSTEM}
else
  export PATH=${G4WORKDIR}/bin/${G4SYSTEM}:${PATH}
fi


#----------------------------------------------------------------------------
# Library build setup
#
export G4LIB_BUILD_SHARED=1



#----------------------------------------------------------------------------
# Resource file paths
# N.B. Data Library Paths are only set if they were installed by CMake
#
# ABLA Data not installed
# EMLOW Data not installed
# Photon Evaporation Data not installed
# NDL Data not installed
# Neutron Cross Section Data not installed
# Shell Ionization Cross Section Data not installed
# Radioactive Decay Data not installed
# RealSurface Data not installed

#----------------------------------------------------------------------------
# Optional components.
#
#----------------------------------------------------------------------------
# CLHEP setup
#
# USING INTERNAL CLHEP





#----------------------------------------------------------------------------
# ZLIB Setup
#
export G4LIB_USE_ZLIB=1


#----------------------------------------------------------------------------
# GDML Setup
#
# NOT BUILT WITH GDML SUPPORT


#----------------------------------------------------------------------------
# G3ToG4 Setup
#
# NOT BUILT WITH G3TOG4 SUPPORT

#----------------------------------------------------------------------------
# USER INTERFACE AND VISUALIZATION MODULES
#
#----------------------------------------------------------------------------
# Terminal UI
export G4UI_USE_TCSH=1
# WIN32 TERMINAL UI NOT AVAILABLE ON Darwin

#----------------------------------------------------------------------------
# Qt UI/Vis
#
# NOT BUILT WITH QT INTERFACE


#----------------------------------------------------------------------------
# Xm UI/Vis
#
# NOT BUILT WITH XM INTERFACE


#----------------------------------------------------------------------------
# Network DAWN driver
#
# NOT BUILT WITH NETWORK DAWN SUPPORT

#----------------------------------------------------------------------------
# Network VRML driver
#
# NOT BUILT WITH NETWORK VRML SUPPORT

#----------------------------------------------------------------------------
# OpenInventor
#
# NOT BUILT WITH INVENTOR SUPPORT

#----------------------------------------------------------------------------
# X11 OpenGL
#
# NOT BUILT WITH OPENGL(X11) SUPPORT

#----------------------------------------------------------------------------
# Win32 OpenGL
#
# NOT BUILT WITH OPENGL(WIN32) SUPPORT

#----------------------------------------------------------------------------
# X11 Raytracer 
#
# NOT BUILT WITH RAYTRACER(X11) SUPPORT

