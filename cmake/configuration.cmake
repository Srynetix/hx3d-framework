## Flags C++

set(
  NEEDED_CXX_FLAGS
  "-std=c++11\
  -fdiagnostics-color=always\
  -Wall\
  -g"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NEEDED_CXX_FLAGS}")
