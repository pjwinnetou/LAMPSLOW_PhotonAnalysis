# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_IFW "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMPONENTS_ALL "Development;Runtime;Unspecified")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "PackageMaker;TGZ")
SET(CPACK_INSTALL_CMAKE_PROJECTS "/Users/jpark/tools/Geant4/Default;Geant4;ALL;/")
SET(CPACK_INSTALL_PREFIX "/usr/local")
SET(CPACK_MODULE_PATH "/Users/jpark/tools/Geant4/geant4.9.5.p02_source/cmake/Modules")
SET(CPACK_NSIS_DISPLAY_NAME "Geant4 9.5")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_PACKAGE_NAME "Geant4 9.5")
SET(CPACK_OUTPUT_CONFIG_FILE "/Users/jpark/tools/Geant4/Default/CPackConfig.cmake")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION "Geant4 Toolkit")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/Users/jpark/tools/Geant4/Default/README.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Geant4 Toolkit")
SET(CPACK_PACKAGE_FILE_NAME "Geant4-9.5.1-Darwin")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Geant4 9.5")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Geant4 9.5")
SET(CPACK_PACKAGE_NAME "Geant4")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Geant4 Collaboration")
SET(CPACK_PACKAGE_VERSION "9.5.1")
SET(CPACK_PACKAGE_VERSION_MAJOR "9")
SET(CPACK_PACKAGE_VERSION_MINOR "5")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
SET(CPACK_PROJECT_CONFIG_FILE "/Users/jpark/tools/Geant4/Default/CMakeCPackOptions.cmake")
SET(CPACK_RESOURCE_FILE_LICENSE "/Users/jpark/tools/Geant4/Default/LICENSE.txt")
SET(CPACK_RESOURCE_FILE_README "/Users/jpark/tools/Geant4/Default/README.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "/usr/local/share/cmake-3.3/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TGZ;TBZ2;ZIP")
SET(CPACK_SOURCE_IGNORE_FILES "/Users/jpark/tools/Geant4/Default;/Users/jpark/tools/Geant4/geant4.9.5.p02_source/tests;~$;/CVS/;/.svn/;/\\\\.svn/;/.git/;/\\\\.git/;\\\\.swp$;\\\\.swp$;\\.swp;\\\\.#;/#")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/Users/jpark/tools/Geant4/Default/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_STRIP_FILES "")
SET(CPACK_SOURCE_TBZ2 "")
SET(CPACK_SOURCE_TGZ "")
SET(CPACK_SOURCE_TXZ "")
SET(CPACK_SOURCE_TZ "")
SET(CPACK_SOURCE_ZIP "")
SET(CPACK_SYSTEM_NAME "Darwin")
SET(CPACK_TOPLEVEL_TAG "Darwin")
SET(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/Users/jpark/tools/Geant4/Default/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()

# Configuration for installation type "full"
list(APPEND CPACK_ALL_INSTALL_TYPES full)
set(CPACK_INSTALL_TYPE_FULL_DISPLAY_NAME "Full Installation")

# Configuration for installation type "runtime"
list(APPEND CPACK_ALL_INSTALL_TYPES runtime)
set(CPACK_INSTALL_TYPE_RUNTIME_DISPLAY_NAME "Runtime Installation")

# Configuration for installation type "developer"
list(APPEND CPACK_ALL_INSTALL_TYPES developer)
set(CPACK_INSTALL_TYPE_DEVELOPER_DISPLAY_NAME "Developer Installation")

# Configuration for component "Development"

SET(CPACK_COMPONENTS_ALL Development Runtime Unspecified)
set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "Development Components")
set(CPACK_COMPONENT_DEVELOPMENT_DESCRIPTION "Install all files needed for developing Geant4 applications (headers, makefiles, etc.)")
set(CPACK_COMPONENT_DEVELOPMENT_INSTALL_TYPES developer full)

# Configuration for component "Runtime"

SET(CPACK_COMPONENTS_ALL Development Runtime Unspecified)
set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Geant4 runtime Libraries")
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "Install all Geant4 libraries")
set(CPACK_COMPONENT_RUNTIME_INSTALL_TYPES runtime developer full)

# Configuration for component "Examples"

SET(CPACK_COMPONENTS_ALL Development Runtime Unspecified)
set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Application Examples")
set(CPACK_COMPONENT_EXAMPLES_DESCRIPTION "Install all Geant4 examples")
set(CPACK_COMPONENT_EXAMPLES_INSTALL_TYPES full developer)

# Configuration for component "Data"

SET(CPACK_COMPONENTS_ALL Development Runtime Unspecified)
set(CPACK_COMPONENT_DATA_DISPLAY_NAME "Geant4 Data Files")
set(CPACK_COMPONENT_DATA_DESCRIPTION "Install all Geant4 data files")
set(CPACK_COMPONENT_DATA_INSTALL_TYPES full)
