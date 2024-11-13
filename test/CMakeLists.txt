cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

set(TEST_PROJECT_NAME test-proj)
set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src/parallel-executor)

set(TEST_ALL_SOURCES
    Test_Device.cpp
    Test_EventQueue.cpp
    Test_Events.cpp
    Test_Helpers.cpp
    Test_Reader.cpp
)

add_executable(${TEST_PROJECT_NAME} ${TEST_ALL_SOURCES})

include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(${TEST_PROJECT_NAME} ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
target_link_libraries(${TEST_PROJECT_NAME} parallel-executor)
target_link_libraries(${TEST_PROJECT_NAME} GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(${TEST_PROJECT_NAME})