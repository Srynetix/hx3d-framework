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

#pragma once

#include "hx3d/utils/algorithm.hpp"
#include "hx3d/window/input_handler.hpp"

namespace hx3d {
namespace window {

class InputMultiplexer: public InputHandler {
public:
  InputMultiplexer();

  void registerInput(InputHandler* handler);
  void unregisterInput(InputHandler* handler);
  void clearInputs();

  virtual void onWindowEvent(WindowEvent::Type type) override;
  virtual void onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) override;

  virtual void onMouseReleased(MouseButtonEvent::Button button, glm::vec2 mousePosition) override;
  virtual void onMouseWheel(MouseWheelEvent::Direction direction, glm::vec2 wheelMovement) override;
  virtual void onMouseMotion(glm::vec2 mousePosition, glm::vec2 mouseMovement) override;

  virtual void onTouchDown(glm::vec2 touchPosition, float touchPressure) override;
  virtual void onTouchUp(glm::vec2 touchPosition, float touchPressure) override;
  virtual void onTouchMotion(glm::vec2 touchPosition, glm::vec2 touchMovement, float touchPressure) override;

  virtual void onKeyPressed(KeyEvent::Key key) override;
  virtual void onKeyReleased(KeyEvent::Key key) override;

private:
  std::vector<InputHandler*> _handlers;
};

} /* window */
} /* hx3d */
