set(GAME_NAME "tests")

include(../cmake/system_check.cmake)
include(../cmake/configuration.cmake)

###################
## Needed libraries

set(
  COMMON_LIBRARIES
)

set(
  ANDROID_LIBRARIES

  ${COMMON_LIBRARIES}
)

set(
  IOS_LIBRARIES

  ${COMMON_LIBRARIES}
)

set(
  WINDOWS_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lmingw32 -lSDL2main -lSDL2 -lgtest -mwindows"
)

set(
  LINUX_LIBRARIES

  ${COMMON_LIBRARIES}
  "-lgtest"
)

if (WIN32)
  set(DESKTOP_LIBRARIES ${WINDOWS_LIBRARIES})
else()
  set(DESKTOP_LIBRARIES ${LINUX_LIBRARIES})
endif()

###################
## Include directories

set(GAME_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CORE_ROOT ${GAME_ROOT}/core)
set(CORE_SRC ${CORE_ROOT}/src)

include_directories(${CORE_ROOT}/include)

###################
## Files

include(GameFiles.cmake)

set(
  DESKTOP_FILES

  ${COMMON_FILES}
  ${UNIT_TESTS}
  "${GAME_ROOT}/desktop/main.cpp"
)

#################
## Compilation

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NEEDED_CXX_FLAGS}")

if (ANDROID)
  add_library(${GAME_NAME} SHARED ${COMMON_FILES})
  target_link_libraries(${GAME_NAME} LINK_PUBLIC hx3d ${ANDROID_LIBRARIES})
elseif(IOS)
  add_library(${GAME_NAME} STATIC ${COMMON_FILES})
  target_link_libraries(${GAME_NAME} LINK_PUBLIC hx3d ${IOS_LIBRARIES})
else()
  add_executable(${GAME_NAME} ${DESKTOP_FILES})
  target_link_libraries(${GAME_NAME} LINK_PUBLIC hx3d ${DESKTOP_LIBRARIES})
endif()
