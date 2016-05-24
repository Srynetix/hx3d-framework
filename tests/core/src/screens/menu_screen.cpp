#include "tests/screens/menu_screen.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"
#include "hx3d/window/events.hpp"
#include "hx3d/window/game.hpp"

#include "hx3d/utils/assets.hpp"

/**
Screens list.
*/
#include "tests/screens/test1_simple3d.hpp"
#include "tests/screens/test2_simple3d2.hpp"
#include "tests/screens/test3_simple2d.hpp"
// #include "tests/screens/test4_simpleecs.hpp"
#include "tests/screens/test5_framebuffer.hpp"
// #include "tests/screens/test6_fastbatch.hpp"
// #include "tests/screens/test7_sound.hpp"
// #include "tests/screens/test8_image.hpp"
// #include "tests/screens/test9_interpolation.hpp"
#include "tests/screens/test10_stencil.hpp"
// #include "tests/screens/test11_tweening.hpp"
// #include "tests/screens/test12_particles.hpp"
// #include "tests/screens/test13_gravity.hpp"
#include "tests/screens/test14_buffertest.hpp"
// #include "tests/screens/test15_timers.hpp"
// #include "tests/screens/test16_basicshading.hpp"
// #include "tests/screens/test17_physics_1.hpp"
// #include "tests/screens/test18_2d_3d.hpp"
#include "tests/screens/test19_chipmunk.hpp"

MenuScreen::MenuScreen():
  defaultShader(Core::Assets()->get<Shader>("base")),
  pixShader(Core::Assets()->get<Shader>("pix2D"))
{
  sprite->setTexture(Core::Assets()->get<Texture>("box"));
  sprite->setTint(Color(0, 0, 64));

  logoSprite->setTexture(Core::Assets()->get<Texture>("logo"));

  batch->setCamera(camera);

  glm::vec2 worldSize = Core::App()->getSize();
  buttonWidth = worldSize.x / 10;
  buttonHeight = worldSize.y / 10;

  sprite->transform.size = glm::vec3(buttonWidth, buttonHeight, 0);

  instructions->setContent("touch test to launch. then ESC or Back to go back. ESC or Back here to quit.");
  instructions->transform.position = glm::vec3(worldSize.x / 2.f, 40, 0);

  instructions->setFunction(math::Function(0, 0.5f, [](float& x, float& y, float t) {
    y = std::sin(t) * 2.f;
    x = std::cos(t / 2.f);
  }));

  logoSprite->transform.scale = glm::vec3(0.25, 0.25, 0);
  logoSprite->transform.position = glm::vec3(worldSize.x - 150, worldSize.y - 150, 0);

  screens = std::vector<ScreenInfo> {
    {"Simple 3D", [](){Core::CurrentGame()->setScreen(Make<Test1>());}},
    {"Simple 3D 2", [](){Core::CurrentGame()->setScreen(Make<Test2>());}},
    {"Simple 2D", [](){Core::CurrentGame()->setScreen(Make<Test3>());}},
    // {"Simple ECS", [](){Core::CurrentGame()->setScreen(Make<Test4>());}},
    {"Framebuffer", [](){Core::CurrentGame()->setScreen(Make<Test5>());}},
    // {"Fast Batch 2D", [](){Core::CurrentGame()->setScreen(Make<Test6>());}},
    // {"Sound", [](){Core::CurrentGame()->setScreen(Make<Test7>());}},
    // {"Image", [](){Core::CurrentGame()->setScreen(Make<Test8>());}},
    // {"Interpolations", [](){Core::CurrentGame()->setScreen(Make<Test9>());}},
    {"Stencil", [](){Core::CurrentGame()->setScreen(Make<Test10>());}},
    // {"Tweening", [](){Core::CurrentGame()->setScreen(Make<Test11>());}},
    // {"Particles", [](){Core::CurrentGame()->setScreen(Make<Test12>());}},
    // {"Gravity", [](){Core::CurrentGame()->setScreen(Make<Test13>());}},
    {"Buffer test", [](){Core::CurrentGame()->setScreen(Make<Test14>());}},
    // {"Timers", [](){Core::CurrentGame()->setScreen(Make<Test15>());}},
    // {"Basic Shading", [](){Core::CurrentGame()->setScreen(Make<Test16>());}},
    // {"Physics 1", [](){Core::CurrentGame()->setScreen(Make<Test17>());}},
    // {"2D + 3D", [](){Core::CurrentGame()->setScreen(Make<Test18>());}}
    {"Chipmunk", [](){Core::CurrentGame()->setScreen(Make<Test19>());}}
  };

  buttonCount = worldSize.y / buttonHeight;

  text->setCharacterSize(16);
}

void MenuScreen::show() {
  Core::Events()->registerHandler(this);
}

void MenuScreen::hide() {
  Core::Events()->unregisterHandler(this);
}

void MenuScreen::onTouchDown(glm::vec2 touchPosition, float touchPressure) {
  float screen_x = touchPosition.x * Core::App()->getWidth();
  float screen_y = touchPosition.y * Core::App()->getHeight();

  // glm::vec2 vpc = viewport.screenToWorld(glm::vec2(screen_x, screen_y));
  glm::vec2 vpc = {screen_x, screen_y};
  if (vpc.x < 0 || vpc.y < 0)
    return;

  unsigned int column = vpc.x / buttonWidth;
  unsigned int target = vpc.y / buttonHeight;

  if (target > buttonCount - 1)
    return;

  unsigned int index = target + column * buttonCount;
  if (index < screens.size()) {
    screens[index].func();
  }
}

void MenuScreen::update(float delta) {
  if (Core::CurrentSystem == Core::SystemType::Android) {
    if (Core::Events()->isKeyPressed(KeyEvent::Key::AndroidBack)) {
      Core::CurrentGame()->stop();
    }
  }

  else if (Core::Events()->isKeyPressed(KeyEvent::Key::Escape)) {
    Core::CurrentGame()->stop();
  }

  instructions->setFunctionInit(Core::App()->getElapsedTime() * 2);

  camera->update();
}

void MenuScreen::render() {

  Framebuffer::clear(Color::Black);
  // glm::vec2 worldSize = viewport.getWorldSize();
  glm::vec2 worldSize = Core::App()->getSize();

  batch->setShader(defaultShader);
  batch->begin();
  for (unsigned int i = 0; i < screens.size(); ++i) {

    int column = i / buttonCount;
    int index = i % buttonCount;

    int posX = (buttonWidth / 2) + column * buttonWidth;
    int posY = worldSize.y - index * buttonHeight - (buttonHeight / 2);

    sprite->transform.position = glm::vec3(posX, posY, 0);
    text->transform.position = glm::vec3(sprite->transform.position.x, sprite->transform.position.y, 0.5f);

    text->setContent(screens[i].name);

    batch->draw(sprite);
    batch->draw(text);
  }

  batch->draw(instructions);

  batch->end();

  /** PIX */
  Shader::use(pixShader);
  pixShader->setUniform1f("time", Core::App()->getElapsedTime());
  pixShader->setUniform2f("resolution", glm::vec2(250, 250));
  pixShader->setUniform2f("pixel_size", glm::vec2(5, 5));
  Shader::disable();

  batch->setShader(pixShader);
  batch->begin();
  batch->draw(logoSprite);
  batch->end();
}
