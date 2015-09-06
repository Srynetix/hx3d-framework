#
#     Engine CMakeLists.
#     Copyright (C) 2015 Denis BOURGE
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License as published by the Free Software Foundation; either
#     version 2.1 of the License, or (at your option) any later version.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
#     USA

include(../cmake/system_check.cmake)

##################
## Arguments

set(
  NEEDED_CXX_FLAGS
  "-std=c++11\
  -fdiagnostics-color=always\
  -Wall\
  -g"
)

###################
## Needed libraries

set(
  COMMON_LIBRARIES

  "-lSDL2\
  -lSDL2_image\
  -lSDL2_mixer\
  -lSDL2_net\
  -lfreetype-gl\
  -lfreetype\
  -lBox2D"
)

set(
  LINUX_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lGLEW\
  -lGL"
)

set(
  WINDOWS_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lglew32\
  -lopengl32\
  -lSDL2main"
)

set(
  MACOSX_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lGLEW \
  -framework CoreFoundation\
  -framework OpenGL\
  -framework Cocoa\
  -framework ForceFeedback\
  -framework IOKit\
  -framework Carbon"
)

set(
  ANDROID_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lGLESv2\
  -llog\
  -landroid"
)

if (WIN32)
  set(DESKTOP_LIBRARIES ${WINDOWS_LIBRARIES})
elseif(MACOSX)
  set(DESKTOP_LIBRARIES ${MACOSX_LIBRARIES})
else()
  set(DESKTOP_LIBRARIES ${LINUX_LIBRARIES})
endif()

###################
## Include directories

set(ENGINE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_SRC ${ENGINE_ROOT}/src)
set(TEST_SRC ${ENGINE_ROOT}/tests)

include_directories(${ENGINE_ROOT}/include)

###################
## Files

include(./EngineFiles.cmake)

#################
## Compilation

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NEEDED_CXX_FLAGS}")
set(LIBRARY_NAME "${PROJECT_NAME}")

add_library(${LIBRARY_NAME} SHARED ${COMMON_FILES})

if (ANDROID)
  target_link_libraries(${LIBRARY_NAME} ${ANDROID_LIBRARIES})
else()
  target_link_libraries(${LIBRARY_NAME} ${DESKTOP_LIBRARIES})
endif()

# directories
target_include_directories(${LIBRARY_NAME} PUBLIC ${ENGINE_ROOT}/include)
