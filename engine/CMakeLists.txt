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

include(../cmake/dependencies/system_check.cmake)
include(../cmake/configuration.cmake)

###################
## Needed libraries

set(
  COMMON_LIBRARIES

  "-lfreetype-gl\
  -lfreetype\
  -lchipmunk\
  -lyaml-cpp"
)

set(
  LINUX_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lSDL2\
  -lSDL2_mixer\
  -lepoxy\
  -lmruby\
  -lGL"
)

set(
  WINDOWS_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lSDL2\
  -lSDL2_mixer\
  -lglew32\
  -lopengl32\
  -lSDL2main"
)

set(
  MACOSX_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lGLEW \
  -F${DEPENDENCIES_DIR}/lib/macos/Frameworks\
  -framework CoreFoundation\
  -framework OpenGL\
  -framework Cocoa\
  -framework ForceFeedback\
  -framework IOKit\
  -framework SDL2\
  -framework SDL2_mixer\
  -framework Carbon"
)

set(
  ANDROID_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lSDL2\
  -lSDL2_mixer\
  -lGLESv2\
  -llog\
  -landroid"
)

set(
  IOS_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lSDL2\
  -lSDL2_mixer\
  -framework CoreGraphics\
  -framework AudioToolbox\
  -framework CoreAudio\
  -framework QuartzCore\
  -framework OpenGLES\
  -framework UIKit\
  -framework Foundation\
  -framework GameController\
  -framework MediaPlayer"
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

include(EngineFiles.cmake)

if (AUDIO_PROVIDER STREQUAL "SDL2")
  include(../cmake/implementations/audio/sdl2.cmake)
endif()

if (WINDOW_PROVIDER STREQUAL "SDL2")
  include(../cmake/implementations/window/sdl2.cmake)
elseif(WINDOW_PROVIDER STREQUAL "Dummy")
  include(../cmake/implementations/window/dummy.cmake)
endif()

set(
  COMMON_FILES

  ${CORE_FILES}
  ${AUDIO_FILES}
  ${WINDOW_FILES}
  ${UTILS_FILES}
  ${MATH_FILES}
  ${GRAPHICS_FILES}
  ${GUI_FILES}
  ${NET_FILES}
  ${PHYSICS2D_FILES}
  ${ECS_FILES}
  ${SCRIPTING_FILES}
  ${TWEENS_FILES}
)

#################
## Compilation

set(LIBRARY_NAME "${PROJECT_NAME}")

if (ANDROID)
  add_library(${LIBRARY_NAME} SHARED ${COMMON_FILES})
  target_link_libraries(${LIBRARY_NAME} ${ANDROID_LIBRARIES})
elseif(IOS)
  add_library(${LIBRARY_NAME} STATIC ${COMMON_FILES})
  target_link_libraries(${LIBRARY_NAME} ${IOS_LIBRARIES})
else()
  add_library(${LIBRARY_NAME} SHARED ${COMMON_FILES})
  target_link_libraries(${LIBRARY_NAME} ${DESKTOP_LIBRARIES})
endif()

# directories
target_include_directories(${LIBRARY_NAME} PUBLIC ${ENGINE_ROOT}/include)
