/*
    Event management.
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


    TODO
    > Multi-touch management
    > Gesture management
*/

#ifndef HX3D_CORE_EVENTS
#define HX3D_CORE_EVENTS

#include <SDL2/SDL_events.h>
#include <glm/vec2.hpp>

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class InputHandler;

class KeyEvent {
public:
  enum class Type {
    Pressed = 0,
    Released,
    None
  };

  enum class Key {
    A = 0, B, C, D, E,
    F, G, H, I, J,
    K, L, M, N, O,
    P, Q, R, S, T,
    U, V, W, X, Y, Z,
    Space, Escape, Return,
    AndroidBack, AndroidMenu,
    None
  };
};

class WindowEvent {
public:
  enum class Type {
    Closed = 0,
    Shown,
    Moved,
    None
  };
};

class MouseButtonEvent {
public:
  enum class Type {
    Clicked = 0,
    Released,
    None
  };

  enum class Button {
    Left = 0,
    Middle,
    Right,
    Special1,
    Special2,
    None
  };
};

class MouseWheelEvent {
public:
  enum class Direction {
    Left = 0,
    Right,
    Up,
    Down,
    None
  };
};

class TouchEvent {
public:
  enum class Type {
    Touched = 0,
    Released,
    None
  };
};

///////////////////////

class EventManager {

public:
  EventManager();
  ~EventManager();

  /**
  Test the window state.

  @param type Type
  */
  bool isWindowState(WindowEvent::Type type);

  /**
  Test if a mouse button have been clicked.

  @param button Button
  */
  bool isMouseButtonClicked(MouseButtonEvent::Button button);
  /**
  Test if a mouse button have been relased.

  @param button Button
  */
  bool isMouseButtonReleased(MouseButtonEvent::Button button);
  /**
  Test if a mouse button have just been clicked.

  @param button Button
  */
  bool isMouseButtonJustClicked(MouseButtonEvent::Button button);
  /**
  Test if a mouse button have just been released.

  @param button Button
  */
  bool isMouseButtonJustReleased(MouseButtonEvent::Button button);

  /**
  Test if the mouse wheel have been turned in a direction.

  @param direction Direction
  */
  bool isMouseWheelTurned(MouseWheelEvent::Direction direction);

  /**
  Test if the screen have been touched.
  */
  bool isScreenTouched();
  /**
  Test if the screen have been released.
  */
  bool isScreenReleased();
  /**
  Test if the screen have been just touched.
  */
  bool isScreenJustTouched();
  /**
  Test if the screen have been just released.
  */
  bool isScreenJustReleased();

  /**
  Test if the key have been pressed.

  @param key Key
  */
  bool isKeyPressed(KeyEvent::Key key);
  /**
  Test if the key have been released.

  @param key Key
  */
  bool isKeyReleased(KeyEvent::Key key);
  /**
  Test if the key have just been pressed.

  @param key Key
  */
  bool isKeyJustPressed(KeyEvent::Key key);
  /**
  Test if the key have just been released.

  @param key Key
  */
  bool isKeyJustReleased(KeyEvent::Key key);

  /**
  Get the current mouse position.

  @return Mouse position
  */
  glm::vec2 getMousePosition();
  /**
  Get the current mouse movement.

  @return Mouse movement
  */
  glm::vec2 getMouseMovement();
  /**
  Get the current mouse wheel movement.

  @return Mouse wheel movement
  */
  glm::vec2 getMouseWheelMovement();

  /**
  Get the current touch position.

  @return Touch position
  */
  glm::vec2 getTouchPosition();
  /**
  Get the current touch movement.

  @return Touch movement
  */
  glm::vec2 getTouchMovement();
  /**
  Get the current touch pressure.

  @return Touch pressure
  */
  float getTouchPressure();

  /**
  Emulate the touch system with the mouse.
  This will emulate the touch position and the touch movement.
  When clicked, the touch pressure will be at 1.0.

  @param value True/False
  */
  void emulateTouchWithMouse(bool value);

  /**
  Poll the event queue.
  */
  void poll();

  /**
  Define an input handler.

  @param handler Input handler (Raw ptr)
  */
  void setInputHandler(InputHandler* handler);

  /**
  Define an input handler.

  @param handler Input handler (Ptr)
  */
  void setInputHandler(Ptr<InputHandler> handler);

private:
  bool* _keysReleased;
  bool* _keysPressed;

  bool* _mouseButtonClicked;
  bool* _mouseButtonReleased;

  bool* _mouseWheelTurned;
  bool* _windowEvents;

  bool _screenTouched;
  bool _screenReleased;

  glm::vec2 _mousePosition;
  glm::vec2 _mouseMovement;
  glm::vec2 _mouseWheelMovement;

  glm::vec2 _touchPosition;
  glm::vec2 _touchMovement;

  float _touchPressure;

  bool _touchSimulation;

  InputHandler* _currentHandler;
};

} /* hx3d */

#endif
