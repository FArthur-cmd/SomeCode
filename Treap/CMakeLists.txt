cmake_minimum_required(VERSION 3.14)
project(test_programm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -O1")

file(GLOB INCLUDE_SRC include/*.cpp include/*.c)
file(GLOB INCLUDE_HDR include/*.hpp include/*.h)

# Google tests
find_package(GTest)
enable_testing()

add_executable(
  test_programm
  ${INCLUDE_SRC}
  ${INCLUDE_HDR}
  test.cpp
)

target_link_libraries(
  test_programm
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_programm)
