#include "tests/screens/base_test_screen.hpp"

#include "tests/screens/menu_screen.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/event_manager.hpp"
#include "hx3d/window/game.hpp"

BaseTestScreen::BaseTestScreen() {}
BaseTestScreen::~BaseTestScreen() {}

void BaseTestScreen::pause() {
  Core::Events()->unregisterHandler(this);
}

void BaseTestScreen::resume() {
  Core::Events()->registerHandler(this);
}

void BaseTestScreen::onKeyReleased(KeyEvent::Key key) {
  if (key == KeyEvent::Key::Escape || key == KeyEvent::Key::AndroidBack) {
    Core::CurrentGame()->setScreen(Make<MenuScreen>());
  }
}
