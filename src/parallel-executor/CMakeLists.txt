cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

set(PARALLEL_EXECUTOR_PROJECT_NAME parallel_executor)
set(CMAKE_CXX_STANDARD 14)

set(HEADERS 
    EventQueue.h
    Hierarchy.h
    helpers.h
    includes.h
    Reader.h
)

set(SOURCES
    EventQueue.cpp
    Hierarchy.cpp
    Reader.cpp
)

add_library(${PARALLEL_EXECUTOR_PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)