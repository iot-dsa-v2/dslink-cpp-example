cmake_minimum_required(VERSION 3.6.2)

project(dslink-cpp-example)


set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(DSA_SDK_SOURCE ${PROJECT_SOURCE_DIR}/../deps/sdk-dslink-cpp/src)
set(DSA_SDK_INCLUDE ${PROJECT_SOURCE_DIR}/../deps/sdk-dslink-cpp/include)
set(DSA_SDK_DEPS ${PROJECT_SOURCE_DIR}/../deps/sdk-dslink-cpp/deps)

include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${DSA_SDK_DEPS}/msgpack/include)
include_directories(${DSA_SDK_DEPS}/jansson-build/include)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCES example_main.cc)

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("./include")
include_directories("${DSA_SDK_SOURCE}/sdk")
include_directories("${DSA_SDK_INCLUDE}")

add_executable(example_dslink ${SOURCES})

target_link_libraries(example_dslink dsa_sdk)
target_link_libraries(example_dslink ${Boost_LIBRARIES})
target_link_libraries(example_dslink ${OPENSSL_LIBRARIES})
target_link_libraries(example_dslink crypto)


add_dependencies(example_dslink dsa_sdk)
