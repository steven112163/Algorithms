cmake_minimum_required(VERSION 3.16)

project(Strings)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS ../src/*.hpp)
set(SOURCES main.cpp ${HEADER_FILES})

add_executable(evals ${SOURCES})
target_include_directories(evals PRIVATE ../src)