cmake_minimum_required(VERSION 3.5)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")



project(Automat)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Automat_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Automat_SOURCE_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)


#add_subdirectory(${CMAKE_BINARY_DIR}/../3rdparty/$ENV{GOOGLE_TEST_DIR})



#add_subdirectory(C)


#INSTALL(
#    TARGETS C ClassLib
#    RUNTIME DESTINATION exe/bin
#    LIBRARY DESTINATION exe/lib
#)