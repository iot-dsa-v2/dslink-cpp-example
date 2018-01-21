cmake_minimum_required(VERSION 3.6.2)

include(${CMAKE_SOURCE_DIR}/deps/sdk-dslink-cpp/CMakeListsConfig.txt)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/sdk-dslink-cpp")
add_subdirectory("./src")