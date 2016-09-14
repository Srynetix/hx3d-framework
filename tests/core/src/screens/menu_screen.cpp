#include "tests/screens/menu_screen.hpp"

#include "hx3d/hx3d.hpp"

/**
Screens list.
*/
#include "tests/screens/test1_simple3d.hpp"
// #include "tests/screens/test2_simple3d2.hpp"
#include "tests/screens/test3_simple2d.hpp"
// #include "tests/screens/test4_simpleecs.hpp"
// #include "tests/screens/test5_framebuffer.hpp"
// #include "tests/screens/test6_fastbatch.hpp"
// #include "tests/screens/test7_sound.hpp"
// #include "tests/screens/test8_image.hpp"
// #include "tests/screens/test9_interpolation.hpp"
// #include "tests/screens/test10_stencil.hpp"
// #include "tests/screens/test11_tweening.hpp"
// #include "tests/screens/test12_particles.hpp"
 #include "tests/screens/test13_gravity.hpp"
// #include "tests/screens/test14_buffertest.hpp"
// #include "tests/screens/test15_timers.hpp"
// #include "tests/screens/test16_basicshading.hpp"
// #include "tests/screens/test17_physics_1.hpp"
#include "tests/screens/test18_2d_3d.hpp"
// #include "tests/screens/test19_chipmunk.hpp"
#include "tests/screens/test20_skeleton.hpp"
#include "tests/screens/test21_console.hpp"
#include "tests/screens/test22_gui.hpp"
// #include "tests/screens/test23_overlay_physics.hpp"

#define LOAD_SCREEN(name, klass) {name, [](){Core::CurrentGame()->setScreen(Make<klass>());}}

MenuScreen::MenuScreen():
  defaultShader(Core::Assets()->get<Shader>("base")),
  pixShader(Core::Assets()->get<Shader>("pix2D"))
{
  sprite->setTexture(Core::Assets()->get<Texture>("box"));
  sprite->setTint(Color(0, 0, 64));
  sprite->getGeometry()->getAttributeBuffer("Color").upload(GL_STATIC_DRAW);

  logoSprite->setTexture(Core::Assets()->get<Texture>("logo"));

  batch->setCamera(camera);

  glm::vec2 worldSize = Core::App()->getSize();
  buttonWidth = worldSize.x / 10;
  buttonHeight = worldSize.y / 10;

  sprite->setSize(glm::vec3(buttonWidth, buttonHeight, 0));

  instructions->setContent("touch test to launch. then ESC or Back to go back. ESC or Back here to quit.");
  instructions->setPosition(glm::vec3(worldSize.x / 2.f, 40, 0));

  instructions->setFunction(math::Function(0, 0.5f, [](float& x, float& y, float t) {
    y = std::sin(t) * 2.f;
    x = std::cos(t / 2.f);
  }));

  logoSprite->setScale(glm::vec3(0.25, 0.25, 0));
  logoSprite->setPosition(glm::vec3(worldSize.x - 150, worldSize.y - 150, 0));

  screens = std::vector<ScreenInfo> {
    LOAD_SCREEN("Simple 3D", Test1),
    // LOAD_SCREEN("Simple 3D 2", Test2),
    LOAD_SCREEN("Simple 2D", Test3),
    // LOAD_SCREEN("Simple ECS", Test4),
    // LOAD_SCREEN("Framebuffer", Test5),
    // LOAD_SCREEN("Fast Batch 2D", Test6),
    // LOAD_SCREEN("Sound", Test7),
    // LOAD_SCREEN("Image", Test8),
    // LOAD_SCREEN("Interpolations", Test9),
    // LOAD_SCREEN("Stencil", Test10),
    // LOAD_SCREEN("Tweening", Test11),
    // LOAD_SCREEN("Particles", Test12),
     LOAD_SCREEN("Gravity", Test13),
    // LOAD_SCREEN("Buffer test", Test14),
    // LOAD_SCREEN("Timers", Test15),
    // LOAD_SCREEN("Basic shading", Test16),
    // LOAD_SCREEN("Physics 1", Test17),
    LOAD_SCREEN("2D + 3D", Test18),
    // LOAD_SCREEN("Chipmunk", Test19),
    LOAD_SCREEN("Skeleton", Test20),
    LOAD_SCREEN("Console", Test21),
    LOAD_SCREEN("GUI", Test22),
    // LOAD_SCREEN("Physics Overlay", Test23)
  };

  buttonCount = worldSize.y / buttonHeight;

  text->setCharacterSize(16);
}

MenuScreen::~MenuScreen() {
}

void MenuScreen::resume() {
  Core::Events()->registerHandler(this);
}

void MenuScreen::pause() {
  Core::Events()->unregisterHandler(this);
}

void MenuScreen::resize(int w, int h) {
  // viewport->update(camera, w, h);
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

    sprite->setPosition(glm::vec3(posX, posY, 0));

    text->setPosition(glm::vec3(sprite->getPosition().x, sprite->getPosition().y, 0.5f));
    text->setContent(screens[i].name);

    batch->draw(sprite);
    batch->draw(text);
  }

  batch->draw(instructions);

  batch->end();

  /** PIX */
  Shader::use(pixShader);
  pixShader->setUniform1f("time", Core::App()->getElapsedTime() / 4.f);
  pixShader->setUniform2f("resolution", glm::vec2(250, 250));
  pixShader->setUniform2f("pixel_size", glm::vec2(25, 25));
  Shader::disable();

  batch->setShader(pixShader);
  batch->begin();
  batch->draw(logoSprite);
  batch->end();
}
