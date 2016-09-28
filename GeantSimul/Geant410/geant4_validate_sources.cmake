# - Validate sources listed in sources.cmake with those on disk
# This file is configured by Geant4 to locate all sources.cmake files in the
# source tree used by the current build tree. 
#
# We have to parse the sources.cmake files for the headers and sources 
# because these files use the include_directories command, which is non 
# scriptable. A simple REGEX is used to find all the .cc, .hh and .icc files
# listed in eah sources.cmake file. These lists are compared with a GLOB of
# those in the include and src directories of the module corresponding to the
# sources.cmake file.
#
# Warnings are printed when a mismatch is detected.
#
# Note that certain modules have configurable source lists and so we expect
# these to show a mismatch. We allow for this by providing the variable:
#
#  GEANT4_FALSEPOSITIVE_SOURCES  List of all source files (.cc, .hh, .icc)
#                                that may result in false positive mismatch.
#
# As this file is configured by Geant4's CMake system is SHOULD NOT BE EDITED
#


#----------------------------------------------------------------------------
# List all sources that we know cause false positives, e.g. obsolete,
# but still on disk
#
set(GEANT4_FALSEPOSITIVE_SOURCES
  # - Xaw is deprecated...
  G4UIXaw.hh
  G4UIXaw.cc
  # - OpenGL Wt not yet supported....
  G4OpenGLImmediateWt.hh
  G4OpenGLImmediateWtViewer.hh
  G4OpenGLWtViewer.hh
  G4OpenGLImmediateWt.cc
  G4OpenGLImmediateWtViewer.cc
  G4OpenGLWtViewer.cc
  # - VRML has icc files in the src/ directory. These are only used internally
  # but validate_sources assumes icc files will be in include/
  # They are covered in sources.cmake though!
  G4VRML1SceneHandlerFunc.icc
  G4VRML2SceneHandlerFunc.icc
  )


#----------------------------------------------------------------------------
# First locate our current source tree
#
set(GEANT4_SOURCE_TREE "/Users/jpark/tools/Geant4/geant4.9.5.p02_source/source")
message(STATUS "Scanning source tree ${GEANT4_SOURCE_TREE}")


#----------------------------------------------------------------------------
# Now find all of the sources.cmake files...
#
file(GLOB_RECURSE GEANT4_SOURCESCMAKE_FILES
  ${GEANT4_SOURCE_TREE}/*/sources.cmake
  )
list(LENGTH GEANT4_SOURCESCMAKE_FILES GEANT4_SOURCESCMAKE_COUNT)
message(STATUS "Located ${GEANT4_SOURCESCMAKE_COUNT} sources.cmake files")

#----------------------------------------------------------------------------
# Parse each modules and process...
#
foreach(_sourcesfile ${GEANT4_SOURCESCMAKE_FILES})
  # - Where are we?
  get_filename_component(_sourcesfile_location ${_sourcesfile} PATH)

  # - Find on disk files...
  file(GLOB 
    _ondisk_hh
    RELATIVE ${_sourcesfile_location}/include
    ${_sourcesfile_location}/include/*.hh
    ${_sourcesfile_location}/include/*.icc
    )
  file(GLOB 
    _ondisk_cc
    RELATIVE ${_sourcesfile_location}/src
    ${_sourcesfile_location}/src/*.cc
    )

  # - Find files listed in sources.cmake
  # Ouch, we have to use a READ, because we can't load the module directly
  # due to it using the non scriptable command include_directories.
  file(READ ${_sourcesfile} _sourcesfile_contents)
  string(REGEX MATCHALL "[A-Z0-9a-z_]+\\.cc" _sources_cc "${_sourcesfile_contents}")
  string(REGEX MATCHALL "[A-Z0-9a-z_]+\\.(hh|icc)" _sources_hh "${_sourcesfile_contents}")

  # - If we take the difference of each list (in both directions), then there
  # should be no mismatch if resulting lists are empty.

  # - On disk, but not in sources
  set(_cmp_ondisk ${_ondisk_hh} ${_ondisk_cc})
  set(_cmp_sources ${_sources_hh} ${_sources_cc})
  list(REMOVE_ITEM _cmp_ondisk ${_cmp_sources})
  set(_missing_in_sources ${_cmp_ondisk})

  # - In sources, but not on disk
  set(_cmp_ondisk ${_ondisk_hh} ${_ondisk_cc})
  set(_cmp_sources ${_sources_hh} ${_sources_cc})
  list(REMOVE_ITEM _cmp_sources ${_cmp_ondisk})
  set(_missing_on_disk ${_cmp_sources})

  # - Remove known false positives - can probably move this to above
  # difference calculation.
  if(_missing_in_sources)
    list(REMOVE_ITEM _missing_in_sources ${GEANT4_FALSEPOSITIVE_SOURCES})
  endif()
  if(_missing_on_disk)
    list(REMOVE_ITEM _missing_on_disk ${GEANT4_FALSEPOSITIVE_SOURCES})
  endif()

  # - Report if either list is not empty
  if(_missing_in_sources OR _missing_on_disk)
    message(STATUS "Problems detected in ${_sourcesfile_location}:")
    set(GEANT4_BUILD_ISINCONSISTENT TRUE)

    # - New/Obsolete File Error
    if(_missing_in_sources)
      message(STATUS "Sources on disk but not listed in sources.cmake:")
      foreach(_m ${_missing_in_sources})
        message("  ${_m}")
      endforeach()
    endif()

    # - Removed File Error - In general, should be picked up at standard
    # CMake run time, but we double report here to be paranoid.
    if(_missing_on_disk)
      message(STATUS "Sources listed in sources.cmake but not on disk:")
      foreach(_m ${_missing_on_disk})
        message("  ${_m}")
      endforeach()
    endif()
  endif()
endforeach()

#----------------------------------------------------------------------------
# Final fail?
#
if(GEANT4_BUILD_ISINCONSISTENT)
  message(FATAL_ERROR "Inconsistent Geant4 build detected!")
endif()



