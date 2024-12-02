cmake_minimum_required(VERSION 3.30)
project(lab8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET lab8)

set(COMMON_DIR "../common")

file(GLOB SOURCES
        *.cpp
)
file(GLOB HEADERS
        *.h
        ${COMMON_DIR}/*.h
)

add_executable(${TARGET} ${SOURCES} ${HEADERS})

target_include_directories(${TARGET} PRIVATE ${COMMON_DIR})