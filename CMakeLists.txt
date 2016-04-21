cmake_minimum_required(VERSION 2.8)
project(hx3d)

option(TESTS "TESTS" OFF)

add_subdirectory(engine)

if (TESTS)
  add_subdirectory(tests)
else()
  add_subdirectory(game)
endif()
