#include <gtest/gtest.h>

#include "hx3d/window/application.hpp"

#include "tests/test_game.hpp"
#include "tests/tests.hpp"

using namespace hx3d;
using namespace hx3d::window;

TEST_F(Tests, Screens) {
  Application app;
  app.start(Make<TestGame>());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
