cmake_minimum_required(VERSION 3.24)
project(JVMA C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} src/decompiler.c)

target_link_directories(
        ${PROJECT_NAME}
        PRIVATE
        src
        lib
)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        include
)

target_sources(
        ${PROJECT_NAME}
        PRIVATE
        src/compiler.c
        src/decompiler.c
        src/file_reader.c
        src/utils.c
)