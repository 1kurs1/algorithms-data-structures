cmake_minimum_required(VERSION 3.10)

project(ADS C)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_PCH_PROVIDES, "pch.h")

set(SOURCES
    demo.c
)

set(HEADERS
    pch.h
    stack.h
    queue.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)