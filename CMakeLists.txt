cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(Ava
    VERSION 0.0.1
    DESCRIPTION "Project-ava"
    LANGUAGES C CXX
)

set(PARENT_PROJECT_NAME ${PROJECT_NAME})
set(PARENT_PROJECT_VERSION ${CMAKE_PROJECT_VERSION})
set(PARENT_PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR})

include(cmake/options.cmake)
include(cmake/DefaultCompiler.cmake)

add_subdirectory(external/limine)

if(CMAKE_C_COMPILER_ID MATCHES Clang)
    set(CMAKE_LINKER ld.lld)
    set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
    set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
endif()

add_subdirectory(src/kernel)

include(cmake/ClangTidy.cmake)
include(cmake/ClangFormat.cmake)
include(cmake/Documentation.cmake)
include(cmake/BuildISO.cmake)
include(cmake/RunQEMU.cmake)