#ifndef HX3D_TESTS_BASETESTSCREEN
#define HX3D_TESTS_BASETESTSCREEN

#include "hx3d/core/core.hpp"
#include "hx3d/window/events.hpp"
#include "hx3d/window/input_handler.hpp"
#include "hx3d/window/screen.hpp"

#include "hx3d/graphics/viewports/fit_viewport.hpp"

#include "./menu_screen.hpp"

using namespace hx3d;

class BaseTestScreen: public Screen, public InputHandler {
public:
  BaseTestScreen()
  {
    Core::Events()->setInputHandler(this);
  }

  virtual void onKeyReleased(KeyEvent::Key key) override {
    if (key == KeyEvent::Key::Escape || key == KeyEvent::Key::AndroidBack) {
      Core::CurrentGame()->setScreen(Make<MenuScreen>());
    }
  }

  virtual void update(float delta) override {}
  virtual void render() override {}
};

#endif
