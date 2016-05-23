## Configuration

# Audio
# -> SDL2
if (NOT DEFINED AUDIO_PROVIDER)
  set(AUDIO_PROVIDER "SDL2")
endif()

# Window
# -> Dummy
# -> SDL2
if (NOT DEFINED WINDOW_PROVIDER)
  set(WINDOW_PROVIDER "SDL2")
endif()


if (WINDOW_PROVIDER STREQUAL "SDL2")
  add_definitions(-DSDL2_WINDOW_PROVIDER)
elseif (WINDOW_PROVIDER STREQUAL "Dummy")
  add_definitions(-DDUMMY_WINDOW_PROVIDER)
endif()

if (AUDIO_PROVIDER STREQUAL "SDL2")
  add_definitions(-DSDL2_AUDIO_PROVIDER)
endif()

set(CMAKE_BUILD_TYPE "Debug")

## Flags C++

set(
  NEEDED_CXX_FLAGS
  "-std=c++11\
  -fdiagnostics-color=always\
  -Wall\
  -Wextra\
  -Wno-unused-parameter\
  -g3\
  -ggdb3"
)

IF(NOT ANDROID)
  set(NEEDED_CXX_FLAGS "${NEEDED_CXX_FLAGS} -march=native")
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NEEDED_CXX_FLAGS}")
