set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(${PARENT_PROJECT_NAME}_ARCHITECTURE x86_64 CACHE STRING "CPU architecture to build for")
set_property(CACHE ${PARENT_PROJECT_NAME}_ARCHITECTURE PROPERTY STRINGS x86_64)

option(${PARENT_PROJECT_NAME}_ENABLE_DOXYGEN "Enable Doxygen documentation builds for source." OFF)
option(${PARENT_PROJECT_NAME}_ENABLE_LTO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)." OFF)

if(${PARENT_PROJECT_NAME}_ENABLE_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT result OUTPUT output)

  if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(SEND_ERROR "IPO is not supported: ${output}.")
  endif()
endif()

option(ENABLE_CCACHE "Enable the usage of Ccache, in order to speed up rebuild times." OFF)
find_program(CCACHE_FOUND ccache)

if(CCACHE_FOUND AND ENABLE_CCACHE)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()