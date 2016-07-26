#include <unistd.h>

#include "hx3d/window/application.hpp"
#include "tests/test_game.hpp"

using namespace hx3d;
using namespace hx3d::window;

extern "C" int SDL_main(int argc, char* argv[]) {
  Application app;
  Pointer<Game> game = Make<TestGame>();

  app.start(game);
  game = nullptr;

  return 0;
}
