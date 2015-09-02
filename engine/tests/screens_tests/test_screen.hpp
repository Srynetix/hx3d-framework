#ifndef HX3D_TEST_TESTSCREEN
#define HX3D_TEST_TESTSCREEN

#include "hx3d/core/core.hpp"
#include "hx3d/core/events.hpp"
#include "hx3d/core/input_handler.hpp"
#include "hx3d/core/screen.hpp"

#include "./menu_screen.hpp"

using namespace hx3d;

class TestScreen: public Screen, public InputHandler {
public:
  TestScreen() {
    Core::Events()->setInputHandler(this);
  }

  virtual void onTouchDown(glm::vec2 position, float pressure) override {
    Core::CurrentGame()->setScreen(Make<MenuScreen>());
  }

  virtual void update() override {}
  virtual void render() override {}
};

#endif
