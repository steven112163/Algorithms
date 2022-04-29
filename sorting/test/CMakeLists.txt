cmake_minimum_required(VERSION 3.16)

project(Sorting)
set(CMAKE_CXX_STANDARD 17)

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

set(HEADER_FILES ../src/BubbleSort.hpp)
set(SOURCES sorting_tests.cpp ${HEADER_FILES})

add_executable(tests ${SOURCES})
target_include_directories(tests PRIVATE ../src)
target_link_libraries(tests gtest_main)

gtest_discover_tests(tests)