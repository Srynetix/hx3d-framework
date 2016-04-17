set(
  SDL2_IMPL_PATH

  ${ENGINE_ROOT}/implementations/sdl2
)

set(
  WINDOW_FILES
  ${WINDOW_FILES}

  "${SDL2_IMPL_PATH}/window/application.cpp"
  "${SDL2_IMPL_PATH}/window/event_manager.cpp"
)
