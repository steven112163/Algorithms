cmake_minimum_required(VERSION 3.16)

project(Sorting)
set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS ../src/*.hpp)
set(SOURCES main.cpp ${HEADER_FILES})

add_executable(evals ${SOURCES})
target_compile_options(evals PRIVATE -O3)
target_include_directories(evals PRIVATE ../src)