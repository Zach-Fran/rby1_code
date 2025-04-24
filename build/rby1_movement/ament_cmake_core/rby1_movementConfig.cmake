# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_rby1_movement_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED rby1_movement_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(rby1_movement_FOUND FALSE)
  elseif(NOT rby1_movement_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(rby1_movement_FOUND FALSE)
  endif()
  return()
endif()
set(_rby1_movement_CONFIG_INCLUDED TRUE)

# output package information
if(NOT rby1_movement_FIND_QUIETLY)
  message(STATUS "Found rby1_movement: 0.0.0 (${rby1_movement_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'rby1_movement' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${rby1_movement_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(rby1_movement_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${rby1_movement_DIR}/${_extra}")
endforeach()
