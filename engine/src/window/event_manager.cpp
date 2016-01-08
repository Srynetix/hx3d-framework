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

#include "hx3d/window/event_manager.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"

namespace hx3d {
namespace window {

EventManager::EventManager() {
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
  _currentHandler = nullptr;
}

EventManager::~EventManager() {
  delete[] _keysPressed;
  delete[] _keysReleased;

  delete[] _mouseButtonClicked;
  delete[] _mouseButtonReleased;

  delete[] _mouseWheelTurned;
  delete[] _windowEvents;
}

bool EventManager::isWindowState(WindowEvent::Type type) {
  unsigned int position = static_cast<unsigned int>(type);
  bool value = _windowEvents[position];
  if (value)
    _windowEvents[position] = false;

  return value;
}

bool EventManager::isMouseButtonClicked(MouseButtonEvent::Button button) {
  unsigned int position = static_cast<unsigned int>(button);
  return _mouseButtonClicked[position];
}

bool EventManager::isMouseButtonReleased(MouseButtonEvent::Button button) {
  unsigned int position = static_cast<unsigned int>(button);
  return _mouseButtonReleased[position];
}

bool EventManager::isMouseButtonJustClicked(MouseButtonEvent::Button button) {
  unsigned int position = static_cast<unsigned int>(button);
  bool value = _mouseButtonClicked[position];
  if (value)
    _mouseButtonClicked[position] = false;

  return value;
}

bool EventManager::isMouseButtonJustReleased(MouseButtonEvent::Button button) {
  unsigned int position = static_cast<unsigned int>(button);
  bool value = _mouseButtonReleased[position];
  if (value)
    _mouseButtonReleased[position] = false;

  return value;
}

bool EventManager::isMouseWheelTurned(MouseWheelEvent::Direction direction) {
  unsigned int position = static_cast<unsigned int>(direction);
  bool value = _mouseWheelTurned[position];
  if (value)
    _mouseWheelTurned[position] = false;

  return value;
}

bool EventManager::isScreenTouched() {
  return _screenTouched;
}

bool EventManager::isScreenReleased() {
  return _screenReleased;
}

bool EventManager::isScreenJustTouched() {
  bool value = _screenTouched;
  if (value)
    _screenTouched = false;

  return value;
}

bool EventManager::isScreenJustReleased() {
  bool value = _screenReleased;
  if (value)
    _screenReleased = false;

  return value;
}

bool EventManager::isKeyPressed(KeyEvent::Key key) {
  unsigned int position = static_cast<unsigned int>(key);
  return _keysPressed[position];
}

bool EventManager::isKeyReleased(KeyEvent::Key key) {
  unsigned int position = static_cast<unsigned int>(key);
  return _keysReleased[position];
}

bool EventManager::isKeyJustPressed(KeyEvent::Key key) {
  unsigned int position = static_cast<unsigned int>(key);
  bool value = _keysPressed[position];
  if (value)
    _keysPressed[position] = false;

  return value;
}

bool EventManager::isKeyJustReleased(KeyEvent::Key key) {
  unsigned int position = static_cast<unsigned int>(key);
  bool value = _keysReleased[position];
  if (value)
    _keysReleased[position] = false;

  return value;
}

glm::vec2 EventManager::getMousePosition() {
  return _mousePosition;
}

glm::vec2 EventManager::getMouseMovement() {
  return _mouseMovement;
}

glm::vec2 EventManager::getMouseWheelMovement() {
  return _mouseWheelMovement;
}

glm::vec2 EventManager::getTouchPosition() {
  return _touchPosition;
}

glm::vec2 EventManager::getScreenConvertedTouchPosition() {
  auto screen_size = Core::App()->getSize();
  return {_touchPosition.x * screen_size.x, _touchPosition.y * screen_size.y};
}

glm::vec2 EventManager::getTouchMovement() {
  return _touchMovement;
}

float EventManager::getTouchPressure() {
  return _touchPressure;
}

void EventManager::emulateTouchWithMouse(bool value) {
  _touchSimulation = value;
}

void EventManager::setInputHandler(Ptr<InputHandler> handler) {
  _currentHandler = handler.get();
}

void EventManager::setInputHandler(InputHandler* handler) {
  _currentHandler = handler;
}

} /* window */
} /* hx3d */
