/*
    Input handling.
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

#ifndef HX3D_WINDOW_INPUTHANDLER
#define HX3D_WINDOW_INPUTHANDLER

#include "hx3d/window/events.hpp"

#include <glm/glm.hpp>

namespace hx3d {

class InputHandler {
public:
  virtual void onWindowEvent(WindowEvent::Type type) {}

  virtual void onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) {}
  virtual void onMouseReleased(MouseButtonEvent::Button button, glm::vec2 mousePosition) {}
  virtual void onMouseWheel(MouseWheelEvent::Direction direction, glm::vec2 wheelMovement) {}
  virtual void onMouseMotion(glm::vec2 mousePosition, glm::vec2 mouseMovement) {}

  virtual void onTouchDown(glm::vec2 touchPosition, float touchPressure) {}
  virtual void onTouchUp(glm::vec2 touchPosition, float touchPressure) {}
  virtual void onTouchMotion(glm::vec2 touchPosition, glm::vec2 touchMovement, float touchPressure) {}

  virtual void onKeyPressed(KeyEvent::Key key) {}
  virtual void onKeyReleased(KeyEvent::Key key) {}
};

} /* hx3d */

#endif /* HX3D_WINDOW_INPUTHANDLER */
