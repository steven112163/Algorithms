cmake_minimum_required(VERSION 3.16)

project(Strings)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
enable_testing()

file(GLOB HEADER_FILES CONFIGURE_DEPENDS ../src/*.hpp)
set(SOURCES string_tests.cpp ${HEADER_FILES})

add_executable(tests ${SOURCES})
target_compile_options(tests PRIVATE -O3)
target_include_directories(tests PRIVATE ../src)
target_link_libraries(tests PRIVATE gtest_main)

gtest_discover_tests(tests)