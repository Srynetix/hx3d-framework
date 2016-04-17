set(
  SDL2_IMPL_PATH

  ${ENGINE_ROOT}/implementations/sdl2
)

set(
  WINDOW_FILES
  ${WINDOW_FILES}

  "${SDL2_IMPL_PATH}/audio/music.cpp"
)
