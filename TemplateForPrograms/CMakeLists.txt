cmake_minimum_required(VERSION 3.14)
project(test_programm)

set(CMAKE_CXX_STANDARD 20)

# Google tests
find_package(GTest)
enable_testing()

# for build_test executable should be test_programm
add_executable(
  test_programm
  test.cpp
)
target_link_libraries(
  test_programm
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_programm)
