set(
  DUMMY_IMPL_PATH

  ${ENGINE_ROOT}/implementations/dummy
)

set(
  WINDOW_FILES
  ${WINDOW_FILES}

  "${DUMMY_IMPL_PATH}/window/application.cpp"
  "${DUMMY_IMPL_PATH}/window/event_manager.cpp"
)
