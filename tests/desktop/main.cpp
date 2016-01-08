#include <gtest/gtest.h>

#include "hx3d/window/sdl2/sdl2_application.hpp"
#include "hx3d/window/application_config.hpp"

#include "tests/test_game.hpp"
#include "tests/tests.hpp"

using namespace hx3d;
using namespace hx3d::window;

TEST_F(Tests, Screens) {
  ApplicationConfig config;
  config.title = "Tests";
  config.width = 1440;
  config.height = 900;

  SDL2Application app(config);
  app.start(Make<TestGame>());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
