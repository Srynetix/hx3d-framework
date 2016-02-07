set(GAME_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CORE_ROOT ${GAME_ROOT}/core)
set(CORE_SRC ${CORE_ROOT}/src)

set(
UNIT_TESTS

"${CORE_SRC}/core/core_test.cpp"

"${CORE_SRC}/ecs/scene_graph_tests.cpp"
"${CORE_SRC}/math/number_utils.cpp"
"${CORE_SRC}/utils/log_test.cpp"
"${CORE_SRC}/utils/algos_test.cpp"
"${CORE_SRC}/utils/property_test.cpp"

# Put your other tests here
#       "${CORE_SRC}/other.cpp"

)

set(
COMMON_FILES

"${CORE_SRC}/screens/menu_screen.cpp"

"${CORE_SRC}/test_game.cpp"

)
