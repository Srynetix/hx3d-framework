/*
    Input handler.
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

#include "hx3d/window/input_handler.hpp"

namespace hx3d {
namespace window {

void InputHandler::onWindowEvent(WindowEvent::Type type) {}
void InputHandler::onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) {}
void InputHandler::onMouseReleased(MouseButtonEvent::Button button, glm::vec2 mousePosition) {}
void InputHandler::onMouseWheel(MouseWheelEvent::Direction direction, glm::vec2 wheelMovement) {}
void InputHandler::onMouseMotion(glm::vec2 mousePosition, glm::vec2 mouseMovement) {}

void InputHandler::onTouchDown(glm::vec2 touchPosition, float touchPressure) {}
void InputHandler::onTouchUp(glm::vec2 touchPosition, float touchPressure) {}
void InputHandler::onTouchMotion(glm::vec2 touchPosition, glm::vec2 touchMovement, float touchPressure) {}

void InputHandler::onKeyPressed(KeyEvent::Key key) {}
void InputHandler::onKeyReleased(KeyEvent::Key key) {}

} /* window */
} /* hx3d */
