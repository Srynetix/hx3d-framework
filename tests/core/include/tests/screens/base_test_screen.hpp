#ifndef HX3D_TESTS_BASETESTSCREEN
#define HX3D_TESTS_BASETESTSCREEN

#include "hx3d/core/core.hpp"
#include "hx3d/core/events.hpp"
#include "hx3d/core/input_handler.hpp"
#include "hx3d/core/screen.hpp"

#include "./menu_screen.hpp"

using namespace hx3d;

class BaseTestScreen: public Screen, public InputHandler {
public:
  BaseTestScreen() {
    Core::Events()->setInputHandler(this);
  }

  virtual void onKeyReleased(KeyEvent::Key key) override {
    if (key == KeyEvent::Key::Escape || key == KeyEvent::Key::AndroidBack) {
      Core::CurrentGame()->setScreen(Make<MenuScreen>());
    }
  }

  virtual void update() override {}
  virtual void render() override {}
};

#endif
