cmake_minimum_required(VERSION 3.6.2)
set(TEST_NAME example_test)

# add sources
set(TEST_SOURCES example_test.cc)

set(TEST_LIBS ${TEST_LIBS} ${GTEST_BOTH_LIBRARIES})

include_directories(${Boost_INCLUDE_DIRS})
set(TEST_LIBS ${TEST_LIBS} ${Boost_LIBRARIES})

include_directories(${OPENSSL_INCLUDE_DIR})
set(TEST_LIBS ${TEST_LIBS} ${OPENSSL_LIBRARIES})
set(TEST_LIBS ${TEST_LIBS} ${DSA_SDK_LIBRARY})

set(DSA_SDK_SOURCE ${SDK_PROJECT_SOURCE_DIR}/src)
set(DSA_SDK_INCLUDE ${SDK_PROJECT_SOURCE_DIR}/include)
set(DSA_SDK_DEPS ${SDK_PROJECT_SOURCE_DIR}/deps)

include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})
include_directories(${DSA_SDK_INCLUDE})
include_directories(${DSA_SDK_DEPS}/msgpack/include)
include_directories(${DSA_SDK_DEPS}/jansson-build/include)
include_directories(${Boost_INCLUDE_DIR})

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${DSA_SDK_SOURCE}/sdk")
include_directories("${DSA_SDK_INCLUDE}")

add_executable(${TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_NAME} ${TEST_LIBS})

if (NOT PREBUILT_SDK_PATH)
    add_dependencies(${TEST_NAME} ${DSA_SDK_LIBRARY})
endif ()