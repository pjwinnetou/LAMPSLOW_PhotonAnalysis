# This file is configured at cmake time, and loaded at cpack time.
# To pass variables to cpack from cmake, they must be configured
# in this file.  

# This file is configured at cmake time, and loaded at cpack time.
# To pass variables to cpack from cmake, they must be configured
# in this file.  

if(CPACK_GENERATOR MATCHES "NSIS")
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of two (2) backlasshes.
  set(CPACK_PACKAGE_ICON "/Users/jpark/tools/Geant4/geant4.9.5.p02_source\\cmake\\Templates\\g4_small.bmp")
  set(CPACK_NSIS_MUI_ICON "/Users/jpark/tools/Geant4/geant4.9.5.p02_source\\cmake\\Templates\\G4.ico")
  set(CPACK_NSIS_MUI_UNIICON "/Users/jpark/tools/Geant4/geant4.9.5.p02_source\\cmake\\Templates\\G4.ico")
  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
  set(CPACK_NSIS_HELP_LINK "http:\\\\www.geant4.org")
  set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\www.geant4.org")
  set(CPACK_NSIS_CONTACT "gabriele.cosmo@cern.ch")
  set(CPACK_NSIS_MODIFY_PATH ON)
endif()


if("${CPACK_GENERATOR}" STREQUAL "PackageMaker")
  set(CPACK_PACKAGING_INSTALL_PREFIX "/${CPACK_PACKAGE_INSTALL_DIRECTORY}")
  set(CPACK_PACKAGE_DEFAULT_LOCATION "/Applications")
endif()
