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

#pragma once

#include "hx3d/window/events.hpp"

#include <string>
#include <glm/vec2.hpp>

namespace hx3d {
namespace window {

/**
@brief Input management: use with screens !
*/
class InputHandler {
public:
  /**
  @brief When a window event occur

  @param type Window event type
  */
  virtual void onWindowEvent(WindowEvent::Type type);

  /**
  @brief When a mouse click event occur

  @param button         Mouse button
  @param mousePosition  Mouse position
  */
  virtual void onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition);

  /**
  @brief When a mouse click release event occur

  @param button         Mouse button
  @param mousePosition  Mouse position
  */
  virtual void onMouseReleased(MouseButtonEvent::Button button, glm::vec2 mousePosition);

  /**
  @brief When a mouse wheel event occur

  @param direction      Wheel direction
  @param wheelMovement  Wheel movement
  */
  virtual void onMouseWheel(MouseWheelEvent::Direction direction, glm::vec2 wheelMovement);

  /**
  @brief When a mouse move event occur

  @param mousePosition  Mouse position
  @param mouseMovement  Mouse movement
  */
  virtual void onMouseMotion(glm::vec2 mousePosition, glm::vec2 mouseMovement);

  /**
  @brief When a touch down event occur

  @param touchPosition  Touch position
  @param touchPressure  Touch pressure
  */
  virtual void onTouchDown(glm::vec2 touchPosition, float touchPressure);

  /**
  @brief When a touch up event occur

  @param touchPosition  Touch position
  @param touchPressure  Touch pressure
  */
  virtual void onTouchUp(glm::vec2 touchPosition, float touchPressure);

  /**
  @brief When a touch move event occur

  @param touchPosition  Touch position
  @param touchMovement  Touch movement
  @param touchPressure  Touch pressure
  */
  virtual void onTouchMotion(glm::vec2 touchPosition, glm::vec2 touchMovement, float touchPressure);

  /**
  @brief When a key is pressed

  @param key Key
  */
  virtual void onKeyPressed(KeyEvent::Key key);

  /**
  @brief When a key is released

  @param key Key
  */
  virtual void onKeyReleased(KeyEvent::Key key);

  /**
  @brief When input is entered

  @param text String
  */
  virtual void onTextInput(std::string text);
};

} /* window */
} /* hx3d */
