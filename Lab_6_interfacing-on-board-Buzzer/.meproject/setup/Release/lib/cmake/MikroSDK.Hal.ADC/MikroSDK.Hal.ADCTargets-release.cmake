#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MikroSDK.Hal.ADC" for configuration "Release"
set_property(TARGET MikroSDK.Hal.ADC APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MikroSDK.Hal.ADC PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "MikroC"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/lib_hal_adc.a"
  )

list(APPEND _cmake_import_check_targets MikroSDK.Hal.ADC )
list(APPEND _cmake_import_check_files_for_MikroSDK.Hal.ADC "${_IMPORT_PREFIX}/lib/lib_hal_adc.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
