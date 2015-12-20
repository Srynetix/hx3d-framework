#include "tests/test_game.hpp"

#include "tests/screens/menu_screen.hpp"

#include "hx3d/utils/assets.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/event_manager.hpp"

using namespace hx3d;

void TestGame::create() {

  /** Want to load a texture ?
    *   Core::Assets()->create<Texture>("texture_name", "textures/here.png")
    */

  Core::Assets()->create<Texture>("box", "textures/box.jpg");
  Core::Assets()->create<Texture>("logo", "textures/logo.png");
  Core::Assets()->create<Texture>("fire", "textures/fire.png");
  Core::Assets()->create<Texture>("stickman", "textures/stickman.png");

  Core::Assets()->create<Shader>("pix2D", "shaders/pix2D");
  Core::Assets()->create<Shader>("custom2D", "shaders/custom2D");

  Core::Events()->emulateTouchWithMouse(true);

  this->setScreen(Make<MenuScreen>());
}
