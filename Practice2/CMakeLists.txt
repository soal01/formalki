
cmake_minimum_required(VERSION 3.5)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")

project(Practice2)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Practice2_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Practice2_SOURCE_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

add_executable(Practice2Exe main.cpp)
target_link_libraries(Practice2Exe Algo_lib)

add_subdirectory(${CMAKE_BINARY_DIR}/../3rdparty/$ENV{GOOGLE_TEST_DIR})
add_subdirectory(${CMAKE_SOURCE_DIR}/testing)

set(CMAKE_MODULE_PATH ${Practice2_SOURCE_DIR}/cmake)
include(CodeCoverage)
setup_target_for_coverage_lcov(
          NAME coverage
          EXECUTABLE TestExe
          EXCLUDE "${Practice2_SOURCE_DIR}/src")
