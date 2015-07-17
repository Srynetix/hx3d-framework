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

##################
## Dependencies

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  IF(NOT IOS)
    set(MACOSX true)
  ENDIF()
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LINUX true)
ENDIF()

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies)
include_directories(SYSTEM ../dependencies/include)

if (ANDROID)
  link_directories(${DEPENDENCIES_DIR}/lib/android)
elseif(WIN32)
  link_directories(${DEPENDENCIES_DIR}/lib/windows)
elseif(MACOSX)
  set(CMAKE_MACOSX_RPATH ON)
  link_directories(${DEPENDENCIES_DIR}/lib/macos)
elseif(LINUX)
  link_directories(${DEPENDENCIES_DIR}/lib/linux)
elseif(IOS)
  link_directories(${DEPENDENCIES_DIR}/lib/ios)
endif()

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

set(
  TEST_LIBRARIES

  ${DESKTOP_LIBRARIES}
  "-lgtest"
)

###################
## Include directories

set(ENGINE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_SRC ${ENGINE_ROOT}/src)
set(TEST_SRC ${ENGINE_ROOT}/tests)

include_directories(${ENGINE_ROOT}/include)

###################
## Files

set(
  COMMON_FILES

  "${ENGINE_SRC}/core/application.cpp"
  "${ENGINE_SRC}/core/application_config.cpp"
  "${ENGINE_SRC}/core/game.cpp"
  "${ENGINE_SRC}/core/core.cpp"
  "${ENGINE_SRC}/core/events.cpp"
  "${ENGINE_SRC}/core/screen.cpp"
  "${ENGINE_SRC}/core/screen_adapter.cpp"

  "${ENGINE_SRC}/utils/bitset.cpp"
  "${ENGINE_SRC}/utils/log.cpp"
  "${ENGINE_SRC}/utils/chronometer.cpp"
  "${ENGINE_SRC}/utils/timer.cpp"
  "${ENGINE_SRC}/utils/string.cpp"
  "${ENGINE_SRC}/utils/file.cpp"
  "${ENGINE_SRC}/utils/matrix_queue.cpp"
  "${ENGINE_SRC}/utils/resource.cpp"

  "${ENGINE_SRC}/math/function.cpp"
  "${ENGINE_SRC}/math/vector_utils.cpp"
  "${ENGINE_SRC}/math/random.cpp"

  "${ENGINE_SRC}/graphics/color.cpp"
  "${ENGINE_SRC}/graphics/sprite.cpp"
  "${ENGINE_SRC}/graphics/shader.cpp"
  "${ENGINE_SRC}/graphics/mesh.cpp"
  "${ENGINE_SRC}/graphics/font.cpp"
  "${ENGINE_SRC}/graphics/texture.cpp"
  "${ENGINE_SRC}/graphics/texture_region.cpp"
  "${ENGINE_SRC}/graphics/batch.cpp"
  "${ENGINE_SRC}/graphics/frame_buffer.cpp"
  "${ENGINE_SRC}/graphics/viewport.cpp"
  "${ENGINE_SRC}/graphics/camera.cpp"

  "${ENGINE_SRC}/graphics/viewports/fit_viewport.cpp"
  "${ENGINE_SRC}/graphics/cameras/perspective_camera.cpp"
  "${ENGINE_SRC}/graphics/cameras/orthographic_camera.cpp"
  "${ENGINE_SRC}/graphics/meshes/cube.cpp"
  "${ENGINE_SRC}/graphics/meshes/star.cpp"
  "${ENGINE_SRC}/graphics/meshes/origin.cpp"
  "${ENGINE_SRC}/graphics/utils/attribute_array_buffer.cpp"
  "${ENGINE_SRC}/graphics/utils/index_array_buffer.cpp"
  "${ENGINE_SRC}/graphics/utils/multi_array_buffer.cpp"
  "${ENGINE_SRC}/graphics/utils/transform.cpp"
  "${ENGINE_SRC}/graphics/utils/vbo.cpp"

  "${ENGINE_SRC}/gui/system.cpp"
  "${ENGINE_SRC}/gui/widget.cpp"
  "${ENGINE_SRC}/gui/text.cpp"

  "${ENGINE_SRC}/physics/2d/world.cpp"
  "${ENGINE_SRC}/physics/2d/collision_matrix.cpp"
  "${ENGINE_SRC}/physics/2d/body.cpp"
  "${ENGINE_SRC}/physics/2d/body_def.cpp"
  "${ENGINE_SRC}/physics/2d/debug_draw.cpp"

  "${ENGINE_SRC}/ecs/engine.cpp"
  "${ENGINE_SRC}/ecs/component.cpp"
  "${ENGINE_SRC}/ecs/entity.cpp"
  "${ENGINE_SRC}/ecs/system.cpp"
)

set(
  UNIT_TESTS

  "${TEST_SRC}/log_test.cpp"

  "${TEST_SRC}/screens/screen_one.cpp"
  "${TEST_SRC}/screens/screen_two.cpp"
  "${TEST_SRC}/screens/screen_three.cpp"
)

set(
  TEST_FILES

  ${COMMON_FILES}
  ${UNIT_TESTS}

  "${TEST_SRC}/main.cpp"
)

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

if (BUILD_TESTS)
  # Tests
  add_executable(tests ${TEST_FILES})
  target_link_libraries(tests ${TEST_LIBRARIES})
endif()

# directories
target_include_directories(${LIBRARY_NAME} PUBLIC ${ENGINE_ROOT}/include)
