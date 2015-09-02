#include "./menu_screen.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/core/application.hpp"
#include "hx3d/core/events.hpp"
#include "hx3d/core/game.hpp"

#include "hx3d/utils/assets.hpp"

/**
Screens list.
*/
#include "./screens/test1_simple3d.hpp"
#include "./screens/test2_simple3d2.hpp"
#include "./screens/test3_simple2d.hpp"
#include "./screens/test4_simpleecs.hpp"

using namespace hx3d;

MenuScreen::MenuScreen():
  camera(Make<OrthographicCamera>()),
  text(Core::Assets()->get<Font>("default")),
  instructions(Core::Assets()->get<Font>("default"))
{
  sprite.setTexture(Core::Assets()->get<Texture>("box"));
  sprite.setTint(Color(0, 0, 50));

  batch.setShader(Core::Assets()->get<Shader>("base"));
  batch.setCamera(camera);

  sprite.transform.size = glm::vec3(128, 64, 0);

  instructions.setContent("touch test to launch. re-touch to go back. ESC or Back to quit.");
  instructions.transform.position = glm::vec3(Core::App()->getWidth() - 450, 20, 0);

  screens = std::vector<ScreenInfo> {
    {"Simple 3D", [](){Core::CurrentGame()->setScreen(Make<Test1>());}},
    {"Simple 3D 2", [](){Core::CurrentGame()->setScreen(Make<Test2>());}},
    {"Simple 2D", [](){Core::CurrentGame()->setScreen(Make<Test3>());}},
    {"Simple ECS", [](){Core::CurrentGame()->setScreen(Make<Test4>());}}
  };

  Core::Events()->setInputHandler(this);
}

void MenuScreen::onTouchDown(glm::vec2 touchPosition, float touchPressure) {
  float screen_x = touchPosition.x * Core::App()->getWidth();
  float screen_y = touchPosition.y * Core::App()->getHeight();
  unsigned int column = screen_x / 128;
  unsigned int target = screen_y / 64;

  Log.Info("T: %ld / C: %ld", target, column);

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
}

void MenuScreen::render() {

  Camera::clear(Color(0, 0, 0));

  camera->update();

  batch.begin();

  for (unsigned int i = 0; i < screens.size(); ++i) {
    sprite.transform.position = glm::vec3((128 / 2), Core::App()->getHeight() - i * 64 - (64 / 2), 0);
    text.transform.position = glm::vec3(sprite.transform.position.x - 32, sprite.transform.position.y, 0.5f);

    text.setContent(screens[i].name);

    batch.draw(sprite);
    batch.draw(text);
  }

  batch.draw(instructions, math::Function(Core::App()->getElapsedTime()/10.f, 0.5f, [](float& x, float& y, float t) {
    y = std::sin(t) * 2.f;
    x = std::cos(t / 2.f);
  }));

  batch.end();
}
