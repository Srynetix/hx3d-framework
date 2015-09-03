#include <gtest/gtest.h>

#include "hx3d/core/application.hpp"
#include "hx3d/core/application_config.hpp"

#include "tests/test_game.hpp"
#include "tests/tests.hpp"

using namespace hx3d;

TEST_F(Tests, Screens) {
  ApplicationConfig config;
  config.title = "Tests";

  Application app(Make<TestGame>(), config);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
