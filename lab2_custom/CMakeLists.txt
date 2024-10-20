cmake_minimum_required(VERSION 3.29)
project(lab2_custom LANGUAGES CXX)

set(TARGET lab02)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMMON_DIR "../common")

file(GLOB SOURCES
        *.cpp
)
file(GLOB HEADERS
        *.h
        ${COMMON_DIR}/*.h
)

add_executable(${TARGET} ${SOURCES} ${HEADERS}
        heap.h
        heap.cpp)

target_include_directories(${TARGET} PRIVATE ${COMMON_DIR})
