/*
    Event manager.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#include "hx3d/window/i_event_manager.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/game.hpp"
#include "hx3d/window/application.hpp"
#include "hx3d/window/input_multiplexer.hpp"
#include "hx3d/window/input_handler.hpp"

namespace hx3d {
namespace window {

IEventManager::IEventManager() {
  _keysPressed = new bool[static_cast<unsigned int>(KeyEvent::Key::None) + 1]{false};
  _keysReleased = new bool[static_cast<unsigned int>(KeyEvent::Key::None) + 1]{false};

  _mouseButtonClicked = new bool[static_cast<unsigned int>(MouseButtonEvent::Button::None) + 1]{false};
  _mouseButtonReleased = new bool[static_cast<unsigned int>(MouseButtonEvent::Button::None) + 1]{false};

  _mouseWheelTurned = new bool[static_cast<unsigned int>(MouseWheelEvent::Direction::None) + 1]{false};
  _windowEvents = new bool[static_cast<unsigned int>(WindowEvent::Type::None) + 1]{false};

  _screenTouched = false;
  _screenReleased = false;
  _touchPressure = 0.f;

  _touchSimulation = false;
  _currentHandler = Make<InputMultiplexer>();
}

IEventManager::~IEventManager() {
  delete[] _keysPressed;
  delete[] _keysReleased;

  delete[] _mouseButtonClicked;
  delete[] _mouseButtonReleased;

  delete[] _mouseWheelTurned;
  delete[] _windowEvents;
}

bool IEventManager::isWindowState(WindowEvent::Type type) {
  unsigned int position = static_cast<unsigned int>(type);
  bool value = _windowEvents[position];
  if (value)
    _windowEvents[position] = false;

  return value;
}

bool IEventManager::isMouseButtonClicked(MouseButtonEvent::Button button) {
  unsigned int position = static_cast<unsigned int>(button);
  return _mouseButtonClicked[position];
}

bool IEventManager::isMouseButtonReleased(MouseButtonEvent::Button button) {
  unsigned int position = static_cast<unsigned int>(button);
  return _mouseButtonReleased[position];
}

bool IEventManager::isMouseButtonJustClicked(MouseButtonEvent::Button button) {
  unsigned int position = static_cast<unsigned int>(button);
  bool value = _mouseButtonClicked[position];
  if (value)
    _mouseButtonClicked[position] = false;

  return value;
}

bool IEventManager::isMouseButtonJustReleased(MouseButtonEvent::Button button) {
  unsigned int position = static_cast<unsigned int>(button);
  bool value = _mouseButtonReleased[position];
  if (value)
    _mouseButtonReleased[position] = false;

  return value;
}

bool IEventManager::isMouseWheelTurned(MouseWheelEvent::Direction direction) {
  unsigned int position = static_cast<unsigned int>(direction);
  bool value = _mouseWheelTurned[position];
  if (value)
    _mouseWheelTurned[position] = false;

  return value;
}

bool IEventManager::isScreenTouched() {
  return _screenTouched;
}

bool IEventManager::isScreenReleased() {
  return _screenReleased;
}

bool IEventManager::isScreenJustTouched() {
  bool value = _screenTouched;
  if (value)
    _screenTouched = false;

  return value;
}

bool IEventManager::isScreenJustReleased() {
  bool value = _screenReleased;
  if (value)
    _screenReleased = false;

  return value;
}

bool IEventManager::isKeyPressed(KeyEvent::Key key) {
  unsigned int position = static_cast<unsigned int>(key);
  return _keysPressed[position];
}

bool IEventManager::isKeyReleased(KeyEvent::Key key) {
  unsigned int position = static_cast<unsigned int>(key);
  return _keysReleased[position];
}

bool IEventManager::isKeyJustPressed(KeyEvent::Key key) {
  unsigned int position = static_cast<unsigned int>(key);
  bool value = _keysPressed[position];
  if (value)
    _keysPressed[position] = false;

  return value;
}

bool IEventManager::isKeyJustReleased(KeyEvent::Key key) {
  unsigned int position = static_cast<unsigned int>(key);
  bool value = _keysReleased[position];
  if (value)
    _keysReleased[position] = false;

  return value;
}

glm::vec2 IEventManager::getMousePosition() {
  return _mousePosition;
}

glm::vec2 IEventManager::getMouseMovement() {
  return _mouseMovement;
}

glm::vec2 IEventManager::getMouseWheelMovement() {
  return _mouseWheelMovement;
}

glm::vec2 IEventManager::getTouchPosition() {
  return _touchPosition;
}

glm::vec2 IEventManager::getScreenConvertedTouchPosition() {
  auto screen_size = Core::App()->getSize();
  auto viewport = Core::CurrentGame()->getViewport();
  glm::vec2 pos = {_touchPosition.x * screen_size.x, (1-_touchPosition.y) * screen_size.y};

  return (viewport ? viewport->screenToWorld(pos) : pos);
}

glm::vec2 IEventManager::getTouchMovement() {
  return _touchMovement;
}

float IEventManager::getTouchPressure() {
  return _touchPressure;
}

void IEventManager::emulateTouchWithMouse(bool value) {
  _touchSimulation = value;
}

void IEventManager::registerHandler(InputHandler* handler) {
  _currentHandler->registerInput(handler);
}

void IEventManager::unregisterHandler(InputHandler* handler) {
  _currentHandler->unregisterInput(handler);
}

void IEventManager::clearHandlers() {
  _currentHandler->clearInputs();
}

} /* window */
} /* hx3d */
