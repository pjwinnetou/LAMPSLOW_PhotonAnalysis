# - Geant4 CMake Configuration File for External Projects
# This file is configured by Geant4 for use by an external project
# As this file is configured by Geant4's CMake system it SHOULD NOT BE EDITED
# It defines the following variables
#  Geant4_INCLUDE_DIRS - include directories for Geant4
#  Geant4_DEFINITIONS  - compile definitions needed to use Geant4
#  Geant4_LIBRARIES    - libraries to link against
#  Geant4_CXX_FLAGS    - Recommended CXX flags for the compiler used to
#                        build the Geant4 libraries.
#  Geant4_CXX_FLAGS_<CONFIG> - Recommended CXX flags for build mode CONFIG.
#  Geant4_USE_FILE     - path to a CMake module which may be included to help
#                        setup CMake variables 
#
# You may supply a version number through find_package which will be checked
# against the version of this build. Standard CMake logic is used so that
# the EXACT flag may be passed, and otherwise this build will report itself
# as compatible with the requested version if:
#
#  VERSION_OF_THIS_BUILD >= VERSION_REQUESTED
#
# By default only the core (or kernel) of Geant4 is activated by this module.
# You can specify additional components of Geant4 through the COMPONENTS
# argument to find_package. By default, all core libraries of Geant4 are
# appended to the Geant4_LIBRARIES variable. Specifiying additional components
# will enable a check on the existence of these components, with the following
# per component variables being set:
#
#  Geant4_${COMPONENT}_FOUND    TRUE is the Geant4 library "component" was
#                               found
#
#  Geant4_${COMPONENT}_LIBRARY  Contains the library for the specified
#                               "component" IF the component is a library.
#
# In Geant4, components can be optional subcomponents of an always available
# library. In that case there will be no Geant4_{COMPONENT}_LIBRARY variable.
# These non-library components are generally activated by compile definitions, 
# and in these cases the appropriate definition will be added to the
# Geant4_DEFINITIONS component
#
# If you specify components and use the REQUIRED option to find_package, then
# the module will issue a FATAL_ERROR if this build of Geant does not have 
# the requested component(s).
#
# The list of components available generally corresponds to the optional extras
# that Geant4 can be built with and are:
#
#  gdml              (GDML support)
#
#  ui_tcsh           (TCsh Style Application Command Line Interface)
#  ui_win32          (WIN32 Style Application Command Line Interface)
#
#  motif             (Motif-X11/OpenGL Graphical User Interface)
#  qt                (Qt4/OpenGL Graphical User Interface)
#
#  vis_network_dawn  (Client/Server network interface to DAWN visualization)
#  vis_network_vrml  (Client/Server network interface to VRML visualization)
#  vis_opengl_x11    (OpenGL visualization with X11 interface)
#  vis_opengl_win32  (OpenGL visualization with X11 interface)
#  vis_raytracer_x11 (RayTracer visualization with X11 interface)
#  vis_openinventor  (OpenInventor visualization)
#
# In addition, two 'shorthand' components are defined to help activate all
# available User Interface and Visualization drivers:
# 
#  ui_all            (All available UI drivers)
#  vis_all           (All available Vis drivers)
#
# These never result in a FATAL_ERROR, even if the REQUIRED find_package 
# argument is set. This is because these options do not depend on specific
# components being available.
#
# ===========================================================================
# Variables used by this module which can change the default behaviour of
# this module. They need to be set prior to the call to find_package
#
#  Geant4_CONFIG_DEBUG    If set, enable extra messaging output which can be
#                         helpful in debugging and identifying problems with
#                         the configuration.
#
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# DEBUG : print out the variables passed via find_package arguments
#
if(Geant4_CONFIG_DEBUG)
    message(STATUS "G4CFG_DEBUG : Geant4_VERSION         = ${Geant4_VERSION}")
    message(STATUS "G4CFG_DEBUG : Geant4_FIND_VERSION    = ${Geant4_FIND_VERSION}")
    message(STATUS "G4CFG_DEBUG : Geant4_FIND_REQUIRED   = ${Geant4_FIND_REQUIRED}")
    message(STATUS "G4CFG_DEBUG : Geant4_FIND_COMPONENTS = ${Geant4_FIND_COMPONENTS}")

   foreach(_cpt ${Geant4_FIND_COMPONENTS})
       message(STATUS "G4CFG_DEBUG : Geant4_FIND_REQUIRED_${_cpt} = ${Geant4_FIND_REQUIRED_${_cpt}}")
    endforeach()

    message(STATUS "G4CFG_DEBUG : Geant4_LIBDEPS_LOADED = ${Geant4_LIBDEPS_LOADED}")
endif()


#----------------------------------------------------------------------------
# Locate ourselves, since all other config files should have been installed
# alongside us...
#
get_filename_component(_thisdir "${CMAKE_CURRENT_LIST_FILE}" PATH)


#----------------------------------------------------------------------------
# Provide *recommended* compiler flags used by this build of Geant4
# Don't mess with the actual CMAKE_CXX_FLAGS!!!
# It's up to the user what to do with these
#
set(Geant4_CXX_FLAGS "")
set(Geant4_CXX_FLAGS_DEBUG "-g")
set(Geant4_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(Geant4_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(Geant4_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")

#----------------------------------------------------------------------------
# Set the base compile definitions required to use Geant4
# Components may append to this
# We set VIS/UI_USE directly here, because for now they are, unfortunately,
# always needed for the Examples. 
# However, they ARE NOT required to use Geant4 itself.
#
set(Geant4_DEFINITIONS -DG4_STORE_TRAJECTORY;-DG4VERBOSE)

if(NOT G4UI_NONE)
    list(APPEND Geant4_DEFINITIONS -DG4UI_USE)
endif()

if(NOT G4VIS_NONE)
    list(APPEND Geant4_DEFINITIONS -DG4VIS_USE)
endif()

#----------------------------------------------------------------------------
# Configure the path to the Geant4 headers, using a relative path if possible.
# This is only known at CMake time, so we expand a CMake supplied variable.
#

# Geant4 configured for use from the build tree - absolute paths are used.
set(Geant4_INCLUDE_DIR /Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/analysis/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/digits_hits/detector/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/digits_hits/digits/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/digits_hits/hits/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/digits_hits/scorer/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/digits_hits/utils/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/error_propagation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/event/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/externals/clhep/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/biasing/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/divisions/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/magneticfield/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/navigation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/solids/BREPS/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/solids/Boolean/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/solids/CSG/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/solids/specific/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/geometry/volumes/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/global/HEPGeometry/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/global/HEPNumerics/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/global/HEPRandom/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/global/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/graphics_reps/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/intercoms/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/interfaces/GAG/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/interfaces/basic/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/interfaces/common/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/materials/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/parameterisations/gflash/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/particles/adjoint/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/particles/bosons/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/particles/hadrons/barions/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/particles/hadrons/ions/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/particles/hadrons/mesons/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/particles/leptons/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/particles/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/particles/shortlived/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/particles/utils/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/persistency/ascii/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/persistency/mctruth/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/physics_lists/builders/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/physics_lists/lists/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/biasing/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/cuts/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/decay/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/adjoint/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/dna/processes/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/dna/models/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/dna/utils/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/dna/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/dna/molecules/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/dna/molecules/types/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/highenergy/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/lowenergy/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/muons/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/pii/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/polarisation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/standard/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/utils/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/electromagnetic/xrays/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/cross_sections/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/abrasion/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/binary_cascade/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/cascade/cascade/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/cascade/evaporation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/cascade/utils/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/chiral_inv_phase_space/body/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/chiral_inv_phase_space/cross_sections/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/chiral_inv_phase_space/fragmentation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/chiral_inv_phase_space/interface/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/chiral_inv_phase_space/processes/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/coherent_elastic/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/ablation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/evaporation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/fermi_breakup/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/fission/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/gem_evaporation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/handler/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/multifragmentation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/photon_evaporation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/de_excitation/util/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/em_dissociation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/high_energy/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/im_r_matrix/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/incl/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/inclxx/utils/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/inclxx/incl_physics/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/inclxx/interface/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/isotope_production/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/lend/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/lll_fission/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/low_energy/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/neutron_hp/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/parton_string/diffraction/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/parton_string/hadronization/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/parton_string/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/parton_string/qgsm/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/photolepton_hadron/muon_nuclear/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/pre_equilibrium/exciton_model/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/qmd/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/radioactive_decay/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/quasi_elastic/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/rpg/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/theo_high_energy/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/models/util/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/processes/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/stopping/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/hadronic/util/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/optical/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/parameterisation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/scoring/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/processes/transportation/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/readout/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/run/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/track/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/tracking/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/FukuiRenderer/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/HepRep/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/RayTracer/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/Tree/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/VRML/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/XXX/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/externals/zlib/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/gMocren/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/management/include;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source/visualization/modeling/include)



# Geant4 configured for use CMake modules from source tree
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /Users/jpark/tools/Geant4/geant4.9.5.p02_source/cmake/Modules)


#----------------------------------------------------------------------------
# Configure the path(s) to third party headers.
# This is not a perfect solution to recording dependencies on external
# libraries, but it does ensure that users of THIS Geant4 will pick up
# those it was built against.
# Library dependencies are generally handled through the Geant4LibraryDepends
# file listed below (apart from one exception!)
#
set(Geant4_THIRD_PARTY_INCLUDE_DIRS )

#----------------------------------------------------------------------------
# Construct overall include path for using Geant4
#
set(Geant4_INCLUDE_DIRS
    ${Geant4_INCLUDE_DIR}
    ${Geant4_THIRD_PARTY_INCLUDE_DIRS})


#----------------------------------------------------------------------------
# If we have used imported targets for any third party packages, reimport
# them here, BEFORE we try and import the Geant4 targets which are
# linked againt them.
# Generally, we try and use a standard find_package, but try and force it
# to find the actual package we were built against.
# THIS IS NOT PERFECT!!



#----------------------------------------------------------------------------
# Include the file listing all the imported targets.
# (Not needed if used in the same Geant4 project, or if we have run before) 
# This is always installed in the same location as us...
#
if(NOT CMAKE_PROJECT_NAME STREQUAL Geant4)
  if(NOT Geant4_LIBDEPS_LOADED)
    include("${_thisdir}/Geant4LibraryDepends.cmake")
    set(Geant4_LIBDEPS_LOADED 1)
  endif()
endif()


#----------------------------------------------------------------------------
# Setup components.
# THIS SECTION IS VERY ROUGH AND VERY MUCH CUT AND PASTE.
# TODO: INVESTIGATE TIDY UP WITH LESS PROCESSING.
#----------------------------------------------------------------------------
# Many components are simply present as parts of libraries or always built
# but require additional compile definitions.
#
# - GDML
set(Geant4_gdml_FOUND OFF)
if(Geant4_gdml_FOUND)
  list(REMOVE_ITEM Geant4_FIND_COMPONENTS gdml)
endif()

# - UI : TCSH
set(Geant4_ui_tcsh_FOUND 1)
if(Geant4_ui_tcsh_FOUND)
  if(Geant4_FIND_REQUIRED_ui_tcsh OR Geant4_FIND_REQUIRED_ui_all)
    list(APPEND Geant4_DEFINITIONS -DG4UI_USE_TCSH)
  endif()
  list(REMOVE_ITEM Geant4_FIND_COMPONENTS ui_tcsh)
endif()

# - UI : win32
set(Geant4_ui_win32_FOUND )
if(Geant4_ui_win32_FOUND)
  if(Geant4_FIND_REQUIRED_ui_win32 OR Geant4_FIND_REQUIRED_ui_all)
    list(APPEND 
      Geant4_DEFINITIONS 
      -DG4INTY_USE_WIN32
      -DG4UI_USE_WIN32
      )
  endif()
  list(REMOVE_ITEM Geant4_FIND_COMPONENTS ui_win32)
endif()


# - Visualization : Network DAWN
set(Geant4_vis_dawn_network_FOUND )
if(Geant4_vis_dawn_network_FOUND)
  if(Geant4_FIND_REQUIRED_vis_dawn_network OR Geant4_FIND_REQUIRED_vis_all)
    list(APPEND Geant4_DEFINITIONS -DG4VIS_USE_DAWN)
  endif()
  list(REMOVE_ITEM Geant4_FIND_COMPONENTS vis_dawn_network)
endif()

# - Visualization : Network VRML
set(Geant4_vis_vrml_network_FOUND )
if(Geant4_vis_vrml_network_FOUND)
  if(Geant4_FIND_REQUIRED_vis_vrml_network OR Geant4_FIND_REQUIRED_vis_all)
    list(APPEND Geant4_DEFINITIONS -DG4VIS_USE_VRML)
  endif()
  list(REMOVE_ITEM Geant4_FIND_COMPONENTS vis_vrml_network)
endif()


#----------------------------------------------------------------------------
# Components which requires slightly more complex setup
#
# - Visualization : RayTracerX
set(Geant4_vis_raytracer_x11_FOUND OFF)
if(Geant4_vis_raytracer_x11_FOUND)
  if(Geant4_FIND_REQUIRED_vis_raytracer_x11 OR Geant4_FIND_REQUIRED_vis_all)
    list(APPEND
      Geant4_DEFINITIONS
      -DG4INTY_USE_XT
      -DG4VIS_USE_RAYTRACERX
      )
  endif()
  list(REMOVE_ITEM Geant4_FIND_COMPONENTS vis_raytracer_x11)
endif()


# - Qt (UI and Vis!)
set(Geant4_qt_FOUND OFF)
if(Geant4_qt_FOUND)
  if(Geant4_FIND_REQUIRED_qt OR Geant4_FIND_REQUIRED_ui_all OR
      Geant4_FIND_REQUIRED_vis_all)
    list(APPEND 
      Geant4_DEFINITIONS 
      -DG4INTY_USE_QT
      -DG4UI_USE_QT
      -DG4VIS_USE_OPENGLQT
      )
    set(_geant4_use_opengl_library ON)
  endif()
  list(REMOVE_ITEM Geant4_FIND_COMPONENTS qt)
endif()

# - Motif (UI and Vis!)
set(Geant4_motif_FOUND OFF)
if(Geant4_motif_FOUND)
  if(Geant4_FIND_REQUIRED_motif OR Geant4_FIND_REQUIRED_ui_all OR
      Geant4_FIND_REQUIRED_vis_all)
    list(APPEND
      Geant4_DEFINITIONS
      -DG4INTY_USE_XT
      -DG4UI_USE_XM
      -DG4VIS_USE_OPENGLXM
      )
    set(_geant4_use_opengl_library ON)
  endif()

  list(REMOVE_ITEM Geant4_FIND_COMPONENTS motif)
endif()

# - OpenGL X11
set(Geant4_vis_opengl_x11_FOUND OFF)
if(Geant4_vis_opengl_x11_FOUND)
  if(Geant4_FIND_REQUIRED_vis_opengl_x11 OR Geant4_FIND_REQUIRED_vis_all)
    list(APPEND
      Geant4_DEFINITIONS
      -DG4INTY_USE_XT
      -DG4VIS_USE_OPENGLX
      )
    set(_geant4_use_opengl_library ON)    
  endif()

  list(REMOVE_ITEM Geant4_FIND_COMPONENTS vis_opengl_x11)
endif()

# - OpenGL Win32
set(Geant4_vis_opengl_win32_FOUND )
if(Geant4_vis_opengl_win32_FOUND)
  if(Geant4_FIND_REQUIRED_vis_opengl_win32 OR Geant4_FIND_REQUIRED_vis_all)
    list(APPEND
      Geant4_DEFINITIONS
      -DG4INTY_USE_WIN32
      -DG4VIS_USE_OPENGLWIN32
      )
    set(_geant4_use_opengl_library ON)    
  endif()

  list(REMOVE_ITEM Geant4_FIND_COMPONENTS vis_opengl_win32)
endif()

# - OpenInventor
set(Geant4_vis_openinventor_FOUND OFF)
if(Geant4_vis_openinventor_FOUND)
  if(Geant4_FIND_REQUIRED_vis_openinventor OR Geant4_FIND_REQUIRED_vis_all)
    if(UNIX AND NOT WIN32)
      list(APPEND Geant4_DEFINITIONS
        -DG4INTY_USE_XT
        -DG4VIS_USE_OI
        -DG4VIS_USE_OIX
        )
    elseif(WIN32)
      list(APPEND Geant4_DEFINITIONS
        -G4INTY_USE_WIN32
        -DG4VIS_USE_OI
        -DG4VIS_USE_OIWIN32
        )
    endif()

    set(_geant4_use_inventor_library ON)
  endif()

  list(REMOVE_ITEM Geant4_FIND_COMPONENTS vis_openinventor)
endif()




#----------------------------------------------------------------------------
# Now perform final configuration of libraries...
# We provide FOUND variables for shared and static but for now we don't allow
# users to choose - we prefer shared if available, and fallback to static
#
set(Geant4_shared_FOUND ON)
set(Geant4_static_FOUND OFF)

if(Geant4_shared_FOUND)
    set(_geant4_lib_use_suffix "")
else()
    set(_geant4_lib_use_suffix "-static")
endif()

# The list of libraries probably should be autogenerated, but we hard code
# for now. We don't have to divide the list of shared libraries, but we
# do so for consistency with the way we'll need to do it for static.
# - Always on Vis Components
set(_geant4_internal_libraries
    G4Tree${_geant4_lib_use_suffix}
    G4FR${_geant4_lib_use_suffix} 
    G4GMocren${_geant4_lib_use_suffix}
    G4visHepRep${_geant4_lib_use_suffix}
    G4RayTracer${_geant4_lib_use_suffix}
    G4VRML${_geant4_lib_use_suffix}
)

# G4OpenGL if it's requested.
if(_geant4_use_opengl_library)
    list(APPEND _geant4_internal_libraries
        G4OpenGL${_geant4_lib_use_suffix}
        G4gl2ps${_geant4_lib_use_suffix}
    )
    list(APPEND Geant4_DEFINITIONS -DG4VIS_USE_OPENGL)
endif()

# G4OpenInventor if it's requested.
if(_geant4_use_inventor_library)
  list(APPEND _geant4_internal_libraries
    G4OpenInventor${_geant4_lib_use_suffix}
    )
endif()

# - 'Kernel' libraries
list(APPEND _geant4_internal_libraries
    G4vis_management${_geant4_lib_use_suffix}
    G4modeling${_geant4_lib_use_suffix}
    G4interfaces${_geant4_lib_use_suffix}
    G4persistency${_geant4_lib_use_suffix}
    # G3toG4?
    G4analysis${_geant4_lib_use_suffix}
    G4error_propagation${_geant4_lib_use_suffix}
    G4readout${_geant4_lib_use_suffix}
    G4physicslists${_geant4_lib_use_suffix}
    G4run${_geant4_lib_use_suffix}
    G4event${_geant4_lib_use_suffix}
    G4tracking${_geant4_lib_use_suffix}
    G4parmodels${_geant4_lib_use_suffix}
    G4processes${_geant4_lib_use_suffix}
    G4digits_hits${_geant4_lib_use_suffix}
    G4track${_geant4_lib_use_suffix}
    G4particles${_geant4_lib_use_suffix}
    G4geometry${_geant4_lib_use_suffix}
    G4materials${_geant4_lib_use_suffix}
    G4graphics_reps${_geant4_lib_use_suffix}
    G4intercoms${_geant4_lib_use_suffix}
    G4global${_geant4_lib_use_suffix}
)

# - Any externals built by Geant4
foreach(_extlib G4clhep;G4zlib)
    list(APPEND 
        _geant4_internal_libraries
        ${_extlib}${_geant4_lib_use_suffix}
    )
endforeach()

# - Now set them to Geant4_LIBRARIES
set(Geant4_LIBRARIES ${_geant4_internal_libraries})


#----------------------------------------------------------------------------
# Point the user to the UseGeant4.cmake file which they may wish to include
# to help them with setting up Geant4
#
set(Geant4_USE_FILE ${_thisdir}/UseGeant4.cmake)


#----------------------------------------------------------------------------
# Finally, handle any remaining components.
# We should have dealt with all available components above, except for ui_all
# and vis_all, and removed them from the list of FIND_COMPONENTS so any left 
# we either didn't find or don't know about. Emit a warning if REQUIRED isn't 
# set, or FATAL_ERROR otherwise
#
list(REMOVE_DUPLICATES Geant4_FIND_COMPONENTS)
list(REMOVE_ITEM Geant4_FIND_COMPONENTS ui_all vis_all)

foreach(_remaining ${Geant4_FIND_COMPONENTS})
    if(Geant4_FIND_REQUIRED)
        message(FATAL_ERROR "Geant4 component ${_remaining} not found")
    elseif(NOT Geant4_FIND_QUIETLY)
        message(WARNING " Geant4 component ${_remaining} not found")
    endif()

    unset(Geant4_FIND_REQUIRED_${_remaining})
endforeach()

# And we should be done...

