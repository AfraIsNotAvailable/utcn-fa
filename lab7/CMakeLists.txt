cmake_minimum_required(VERSION 3.30)
project(lab7 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET lab7)

set(COMMON_DIR "../common")

file(GLOB SOURCES
        *.cpp
)
file(GLOB HEADERS
        *.h
        ${COMMON_DIR}/*.h
)

add_executable(${TARGET} ${SOURCES} ${HEADERS}
        dynamic.cpp
        dynamic.h)

target_include_directories(${TARGET} PRIVATE ${COMMON_DIR})