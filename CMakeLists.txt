# ##############################################################################
# OASIS: Open Algebra Software for Inferring Solutions
#
# CMakeLists.txt - Top-level
# ##############################################################################

cmake_minimum_required(VERSION 3.18)
project(Oasis)

include(CTest)
include(FetchContent)

option(OASIS_BUILD_IO "Enables building extra modules for Oasis" OFF)
option(OASIS_BUILD_TESTS "Enables building unit tests for Oasis" ON)
option(OASIS_BUILD_WITH_COVERAGE
       "Enables building Oasis with code coverage enabled" OFF)
option(OASIS_BUILD_PARANOID
       "Enables the -Werror flag friends when building Oasis" OFF)
option(OASIS_BUILD_CLI "Compiles the Oasis CLI" OFF)
option(OASIS_BUILD_JS "Compiles Oasis to WebAssembly via Emscripten" OFF)

if(OASIS_BUILD_CLI OR OASIS_BUILD_JS)
    set(OASIS_BUILD_IO
        ON
        CACHE BOOL
              "OASIS_BUILD_IO enabled by OASIS_BUILD_CLI or OASIS_BUILD_JS"
              FORCE)
endif()

# Adds compiler flags for code coverage. Note that only the Clang compiler is
# currently supported for code coverage.
if(OASIS_BUILD_WITH_COVERAGE)
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate)
endif()

# Fetches dependencies and integrates them into the project.
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0)

# Perhaps one day use Microsoft.GSL if
# https://github.com/microsoft/GSL/issues/991 gets addressed
FetchContent_Declare(
    GSL
    GIT_REPOSITORY "https://github.com/gsl-lite/gsl-lite.git"
    GIT_TAG v0.42.0)

FetchContent_MakeAvailable(Catch2 GSL)

if(NOT OASIS_BUILD_JS)
    include(cmake/FetchBoost.cmake)
endif()

include(cmake/FetchEigen.cmake)

# Processes the CMakeLists.txt for each target.
add_subdirectory(include)
add_subdirectory(src)

if(OASIS_BUILD_IO)
    include(cmake/FetchTinyxml2.cmake)
    add_subdirectory(io)
endif()

if(OASIS_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(OASIS_BUILD_CLI)
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.1.3)

    FetchContent_Declare(
        Isocline
        GIT_REPOSITORY https://github.com/daanx/isocline.git
        GIT_TAG v1.0.9)

    FetchContent_MakeAvailable(fmt Isocline)

    add_subdirectory(cli)
endif()

if(OASIS_BUILD_JS)
    add_subdirectory(bindings/js)
endif()
