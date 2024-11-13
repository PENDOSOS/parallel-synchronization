cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(sync-threads)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory(${CMAKE_SOURCE_DIR}/src/parallel-executor)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/parallel-executor/main.cpp)
target_link_libraries(${PROJECT_NAME} parallel-executor)

enable_testing()
add_subdirectory(test)