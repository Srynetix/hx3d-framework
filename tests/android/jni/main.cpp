#include "hx3d/window/application.hpp"
#include "hx3d/window/application_config.hpp"

#include "tests/test_game.hpp"

using namespace hx3d;
using namespace hx3d::window;

int main(int argc, char** argv) {
  ApplicationConfig config;
  config.title = "Tests";

  Application app(config);
  app.start(Make<TestGame>());

  return 0;
}
