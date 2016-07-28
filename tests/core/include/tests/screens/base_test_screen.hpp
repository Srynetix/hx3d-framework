#pragma once

#include "hx3d/window/events.hpp"
#include "hx3d/window/input_handler.hpp"
#include "hx3d/window/screen.hpp"

using namespace hx3d;
using namespace hx3d::window;

class BaseTestScreen: public Screen, public InputHandler {
public:
  BaseTestScreen();
  virtual ~BaseTestScreen();

  virtual void pause() override;
  virtual void resume() override;

  virtual void onKeyReleased(KeyEvent::Key key) override;
};
