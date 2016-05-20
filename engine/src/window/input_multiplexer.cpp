/*
    Input multiplexer.
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

#include "hx3d/window/input_multiplexer.hpp"

namespace hx3d {
namespace window {

InputMultiplexer::InputMultiplexer() {}

void InputMultiplexer::registerInput(InputHandler* handler) {
  if (std::find(_handlers.begin(), _handlers.end(), handler) == _handlers.end()) {
    _handlers.push_back(handler);
  }
}

void InputMultiplexer::unregisterInput(InputHandler* handler) {
  auto pos = std::find(_handlers.begin(), _handlers.end(), handler);
  if (pos != _handlers.end()) {
    _handlers.erase(pos);
  }
}

void InputMultiplexer::clearInputs() {
  _handlers.clear();
}

void InputMultiplexer::onWindowEvent(WindowEvent::Type type) {
  for (auto& handler: _handlers) {
    handler->onWindowEvent(type);
  }
}

void InputMultiplexer::onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) {
  for (auto& handler: _handlers) {
    handler->onMouseClicked(button, mousePosition);
  }
}

void InputMultiplexer::onMouseReleased(MouseButtonEvent::Button button, glm::vec2 mousePosition) {
  for (auto& handler: _handlers) {
    handler->onMouseReleased(button, mousePosition);
  }
}

void InputMultiplexer::onMouseWheel(MouseWheelEvent::Direction direction, glm::vec2 wheelMovement) {
  for (auto& handler: _handlers) {
    handler->onMouseWheel(direction, wheelMovement);
  }
}

void InputMultiplexer::onMouseMotion(glm::vec2 mousePosition, glm::vec2 mouseMovement) {
  for (auto& handler: _handlers) {
    handler->onMouseMotion(mousePosition, mouseMovement);
  }
}

void InputMultiplexer::onTouchDown(glm::vec2 touchPosition, float touchPressure) {
  for (auto& handler: _handlers) {
    handler->onTouchDown(touchPosition, touchPressure);
  }
}

void InputMultiplexer::onTouchUp(glm::vec2 touchPosition, float touchPressure) {
  for (auto& handler: _handlers) {
    handler->onTouchUp(touchPosition, touchPressure);
  }
}

void InputMultiplexer::onTouchMotion(glm::vec2 touchPosition, glm::vec2 touchMovement, float touchPressure) {
  for (auto& handler: _handlers) {
    handler->onTouchMotion(touchPosition, touchMovement, touchPressure);
  }
}

void InputMultiplexer::onKeyPressed(KeyEvent::Key key) {
  for (auto& handler: _handlers) {
    handler->onKeyPressed(key);
  }
}

void InputMultiplexer::onKeyReleased(KeyEvent::Key key) {
  for (auto& handler: _handlers) {
    handler->onKeyReleased(key);
  }
}

} /* window */
} /* hx3d */
