cmake_minimum_required(VERSION 3.6.2)
set(TEST_NAME example_test)
# add sources
set(TEST_SOURCES example_test.cc)

if (UNIX)
    # Download and unpack googletest-download at configure time
    configure_file(${DSA_SDK_SOURCE_DIR}/CMakeLists.txt.in ${CMAKE_BINARY_DIR}/test/lib/googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib/googletest-download)
    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib/googletest-download)
    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest-download directly to our build. This defines
    # the gtest and gtest_main targets
    if (PREBUILT_SDK_PATH)
        add_subdirectory(${CMAKE_BINARY_DIR}/test/lib/googletest-src
                ${CMAKE_BINARY_DIR}/test/lib/googletest-build)
    endif ()
    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    #if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
    #endif()
    set(GTEST_BOTH_LIBRARIES gtest_main gtest)
endif (UNIX)

if (WIN32)
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
endif (WIN32)
set(TEST_LIBS ${TEST_LIBS} ${GTEST_BOTH_LIBRARIES})


#include(${DSA_SDK_SOURCE_DIR}/CMakeListsTestConfig.txt)

include_directories(${Boost_INCLUDE_DIRS})
set(TEST_LIBS ${TEST_LIBS} ${Boost_LIBRARIES})

include_directories(${OPENSSL_INCLUDE_DIR})
set(TEST_LIBS ${TEST_LIBS} ${OPENSSL_LIBRARIES})
set(TEST_LIBS ${TEST_LIBS} ${DSA_SDK_LIBRARY})

set(DSA_SDK_SOURCE ${DSA_SDK_SOURCE_DIR}/src)
set(DSA_SDK_INCLUDE ${DSA_SDK_SOURCE_DIR}/include)
set(DSA_SDK_DEPS ${DSA_SDK_SOURCE_DIR}/deps)

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