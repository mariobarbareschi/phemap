cmake_minimum_required (VERSION 2.8)
project (phemap)
# The version number.
set (phemap_VERSION_MAJOR 1)
set (phemap_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wfatal-errors")

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/communication ${CMAKE_SOURCE_DIR}/inc/phemap)

# add the executable
add_executable(deviceMain ${CMAKE_SOURCE_DIR}/src/device.cpp)

add_executable(verifierMain ${CMAKE_SOURCE_DIR}/src/verifier.cpp)

add_executable(chainMaker ${CMAKE_SOURCE_DIR}/src/chainMaker.cpp)

target_link_libraries(deviceMain PRIVATE device dummyPuf puf pufChain pufChainFromFile verifier deviceManager deviceProxy deviceServer verifierServer utils)
target_link_libraries(verifierMain PRIVATE device dummyPuf puf pufChain pufChainFromFile verifier deviceManager deviceProxy deviceServer verifierServer utils)

target_link_libraries(chainMaker PRIVATE dummyPuf utils)
