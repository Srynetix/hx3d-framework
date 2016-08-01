#include "tests/test_game.hpp"

#include "tests/screens/menu_screen.hpp"
#include "tests/screens/test18_2d_3d.hpp"

#include "hx3d/utils/assets.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/event_manager.hpp"

#include "hx3d/graphics/transitions/fade_transition.hpp"
#include "hx3d/graphics/transitions/alpha_fade_transition.hpp"
#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/texture.hpp"



using namespace hx3d;

void TestGame::create() {

  /** Want to load a texture ?
    *   Core::Assets()->create<Texture>("texture_name", "textures/here.png")
    */

  // Shader::setProgramAnalyzing(true);

  Core::Assets()->create<Texture>("box", "textures/box.png");
  Core::Assets()->create<Texture>("logo", "textures/logo.png");
  Core::Assets()->create<Texture>("fire", "textures/fire.png");
  Core::Assets()->create<Texture>("stickman", "textures/stickman.png");

  Core::Assets()->create<Shader>("pix2D", "shaders/pix2D");
  Core::Assets()->create<Shader>("custom2D", "shaders/custom2D");
  Core::Assets()->create<Shader>("light3D", "shaders/light3D");
  Core::Assets()->create<Shader>("debugdraw", "shaders/debugdraw/debugdraw");

  Core::Events()->emulateTouchWithMouse(true);

  this->registerScreen<Test18>("2d_3d");
  this->registerScreen<MenuScreen>("menu");

  // auto viewport = Make<FitViewport>(1024, 768);
  // this->setViewport(viewport);

  auto transition = Make<FadeTransition>(this, Color::Black);
  transition->setDuration(1.f);

  this->activateStats(true);
  this->setTransition(transition);
  this->startScreen("2d_3d");
}
