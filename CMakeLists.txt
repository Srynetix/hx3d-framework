cmake_minimum_required(VERSION 2.8)
project(hx3d)

option(TESTS "TESTS" ON)
option(GAME "GAME" OFF)

add_subdirectory(engine)

if (TESTS)
  add_subdirectory(tests)
elseif (GAME)
  add_subdirectory(game)
endif()
