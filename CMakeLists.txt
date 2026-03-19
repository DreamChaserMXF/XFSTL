cmake_minimum_required(VERSION 3.10)
project(XFSTL CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All source files are in STL/STL/
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/STL/STL)

add_executable(xfstl_test
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/multifile_test.cpp
    ${SRC_DIR}/vector_test.cpp
    ${SRC_DIR}/list_test.cpp
    ${SRC_DIR}/deque_test.cpp
    ${SRC_DIR}/adapter_test.cpp
    ${SRC_DIR}/stack_test.cpp
    ${SRC_DIR}/queue_test.cpp
    ${SRC_DIR}/priority_queue_test.cpp
    ${SRC_DIR}/sort_test.cpp
    ${SRC_DIR}/string_test.cpp
)

target_include_directories(xfstl_test PRIVATE ${SRC_DIR})

# Enable warnings
if(MSVC)
    target_compile_options(xfstl_test PRIVATE /W3)
else()
    target_compile_options(xfstl_test PRIVATE -Wall -Wextra)
endif()
