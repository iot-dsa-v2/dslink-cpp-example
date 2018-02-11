cmake_minimum_required(VERSION 3.6.2)
set(TEST_NAME example_test)

# add sources
set(TEST_SOURCES example_test.cc)

set(TEST_LIBS ${TEST_LIBS} ${GTEST_BOTH_LIBRARIES})
set(TEST_LIBS ${TEST_LIBS} ${Boost_LIBRARIES})
set(TEST_LIBS ${TEST_LIBS} ${OPENSSL_LIBRARIES})
set(TEST_LIBS ${TEST_LIBS} ${DSA_SDK_LIBRARY})

add_executable(${TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_NAME} ${TEST_LIBS})

if (NOT PREBUILT_SDK_PATH)
    add_dependencies(${TEST_NAME} ${DSA_SDK_LIBRARY})
endif ()