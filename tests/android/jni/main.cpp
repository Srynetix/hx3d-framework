#include "hx3d/core/application.hpp"
#include "hx3d/core/application_config.hpp"

#include "tests/test_game.hpp"

using namespace hx3d;

int main(int argc, char** argv) {
  ApplicationConfig config;
  config.title = "Tests";

  Application app(Make<TestGame>(), config);

  return 0;
}
