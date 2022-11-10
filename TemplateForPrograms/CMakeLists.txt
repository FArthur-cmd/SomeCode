cmake_minimum_required(VERSION 3.14)
project(test_programm)

set(CMAKE_CXX_STANDARD 20)

file(GLOB INCLUDE_SRC include/*.cpp include/*.c)
file(GLOB INCLUDE_HDR include/*.hpp include/*.h)

if (ADDRESS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    message(STATUS "Address sanitizer is enabled")
endif()

if (UNDEFINED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    message(STATUS "Undefined sanitizer is enabled")
endif()

if (GDB)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    message(STATUS "Debug is enabled")
endif()

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

add_executable(
  main_programm
  ${INCLUDE_SRC}
  ${INCLUDE_HDR}
  main.cpp
)