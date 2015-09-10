#include "tests/screens/menu_screen.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/core/application.hpp"
#include "hx3d/core/events.hpp"
#include "hx3d/core/game.hpp"

#include "hx3d/utils/assets.hpp"

/**
Screens list.
*/
#include "tests/screens/test1_simple3d.hpp"
#include "tests/screens/test2_simple3d2.hpp"
#include "tests/screens/test3_simple2d.hpp"
#include "tests/screens/test4_simpleecs.hpp"
#include "tests/screens/test5_framebuffer.hpp"
#include "tests/screens/test6_physics2d.hpp"
#include "tests/screens/test7_sound.hpp"
#include "tests/screens/test8_image.hpp"
#include "tests/screens/test9_interpolation.hpp"

using namespace hx3d;

MenuScreen::MenuScreen():
  font(Core::Assets()->get<Font>("default")),
  defaultShader(Core::Assets()->get<Shader>("base")),
  pixShader(Core::Assets()->get<Shader>("pix2D")),

  viewport(640, 360, camera),
  text(font),
  instructions(font),

  buttonWidth(64),
  buttonHeight(32)
{
  sprite.setTexture(Core::Assets()->get<Texture>("box"));
  sprite.setTint(Color(0, 0, 50));

  logoSprite.setTexture(Core::Assets()->get<Texture>("logo"));

  batch.setShader(defaultShader);
  batch.setCamera(camera);

  glm::vec2 worldSize = viewport.getWorldSize();

  sprite.transform.size = glm::vec3(buttonWidth, buttonHeight, 0);
  text.transform.scale = glm::vec3(0.5f);

  instructions.setContent("touch test to launch. then ESC or Back to go back. ESC or Back here to quit.");
  instructions.transform.scale = glm::vec3(0.5f);
  instructions.transform.position = glm::vec3(worldSize.x - 300, 20, 0);

  // logoSprite.transform.size = glm::vec3(710, 797, 0);
  logoSprite.transform.scale = glm::vec3(0.25, 0.25, 0);
  logoSprite.transform.position = glm::vec3(worldSize.x - 150, worldSize.y - 100, 0);
  // logoSprite.transform.rotation.z = glm::radians(90.f);

  screens = std::vector<ScreenInfo> {
    {"Simple 3D", [](){Core::CurrentGame()->setScreen(Make<Test1>());}},
    {"Simple 3D 2", [](){Core::CurrentGame()->setScreen(Make<Test2>());}},
    {"Simple 2D", [](){Core::CurrentGame()->setScreen(Make<Test3>());}},
    {"Simple ECS", [](){Core::CurrentGame()->setScreen(Make<Test4>());}},
    {"Framebuffer", [](){Core::CurrentGame()->setScreen(Make<Test5>());}},
    {"Physics 2D", [](){Core::CurrentGame()->setScreen(Make<Test6>());}},
    {"Sound", [](){Core::CurrentGame()->setScreen(Make<Test7>());}},
    {"Image", [](){Core::CurrentGame()->setScreen(Make<Test8>());}},
    {"Interpolations", [](){Core::CurrentGame()->setScreen(Make<Test9>());}}
  };

  Core::Events()->setInputHandler(this);
}

void MenuScreen::resize(int width, int height) {
  viewport.update(width, height, true);
}

void MenuScreen::onTouchDown(glm::vec2 touchPosition, float touchPressure) {
  float screen_x = touchPosition.x * Core::App()->getWidth();
  float screen_y = touchPosition.y * Core::App()->getHeight();

  glm::vec2 vpc = viewport.screenToWorld(glm::vec2(screen_x, screen_y));
  if (vpc.x < 0 || vpc.y < 0)
    return;

  unsigned int column = vpc.x / buttonWidth;
  unsigned int target = vpc.y / buttonHeight;

  if (column == 0 && target < screens.size()) {
    screens[target].func();
  }
}

void MenuScreen::update() {
  if (Core::CurrentSystem == Core::SystemType::Android) {
    if (Core::Events()->isKeyPressed(KeyEvent::Key::AndroidBack)) {
      Core::CurrentGame()->stop();
    }
  }

  else if (Core::Events()->isKeyPressed(KeyEvent::Key::Escape)) {
    Core::CurrentGame()->stop();
  }

  camera.update();
}

void MenuScreen::render() {

  Framebuffer::clear(Color(0, 0, 0));
  glm::vec2 worldSize = viewport.getWorldSize();

  batch.setShader(defaultShader);
  batch.begin();
  for (unsigned int i = 0; i < screens.size(); ++i) {
    sprite.transform.position = glm::vec3((buttonWidth / 2), worldSize.y - i * buttonHeight - (buttonHeight / 2), 0);
    text.transform.position = glm::vec3(sprite.transform.position.x - buttonWidth / 4, sprite.transform.position.y, 0.5f);

    text.setContent(screens[i].name);

    batch.draw(sprite);
    batch.draw(text);
  }

  batch.draw(instructions, math::Function(Core::App()->getElapsedTime()/10.f, 0.5f, [](float& x, float& y, float t) {
    y = std::sin(t) * 2.f;
    x = std::cos(t / 2.f);
  }));
  batch.end();

  /** PIX */
  Shader::use(pixShader);
  pixShader->setUniform1f("time", Core::App()->getElapsedTime() / 100.f);
  pixShader->setUniform2f("resolution", glm::vec2(250, 250));
  pixShader->setUniform2f("pixel_size", glm::vec2(5, 5));
  Shader::disable();

  batch.setShader(pixShader);
  batch.begin();
  batch.draw(logoSprite);
  batch.end();

}
