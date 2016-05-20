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

#ifndef HX3D_WINDOW_EVENTS
#define HX3D_WINDOW_EVENTS

namespace hx3d {
namespace window {

  /**
  @brief Key event
  */
  class KeyEvent {
  public:
    /**
    @brief Key event type
    */
    enum class Type {
      /// @brief Key pressed
      Pressed = 0,
      /// @brief Key released
      Released,
      None
    };

    /**
    @brief Key value
    */
    enum class Key {
      A = 0, B, C, D, E,
      F, G, H, I, J,
      K, L, M, N, O,
      P, Q, R, S, T,
      U, V, W, X, Y, Z,
      Left, Right, Up, Down,
      Space, Escape, Return,
      AndroidBack, AndroidMenu,
      None
    };
  };

  /**
  @brief Window event
  */
  class WindowEvent {
  public:
    /**
    @brief Window event type
    */
    enum class Type {
      /// @brief Window closed
      Closed = 0,
      /// @brief Window shown
      Shown,
      /// @brief Window moved
      Moved,
      None
    };
  };

  /**
  @brief Mouse button event
  */
  class MouseButtonEvent {
  public:
    /**
    @brief Mouse action type
    */
    enum class Type {
      /// @brief Mouse clicked
      Clicked = 0,
      /// @brief Mouse released
      Released,
      None
    };

    /**
    @brief Mouse button value
    */
    enum class Button {
      /// @brief Left click
      Left = 0,
      /// @brief Middle click
      Middle,
      /// @brief Right click
      Right,
      /// @brief Special 1 click
      Special1,
      /// @brief Special 2 click
      Special2,
      None
    };
  };

  /**
  @brief Mouse wheel event
  */
  class MouseWheelEvent {
  public:
    /**
    @brief Mouse wheel direction
    */
    enum class Direction {
      /// @brief Left
      Left = 0,
      /// @brief Right
      Right,
      /// @brief Up
      Up,
      /// @brief Down
      Down,
      None
    };
  };

  /**
  @brief Touch event
  */
  class TouchEvent {
  public:
    /**
    @brief Touch type
    */
    enum class Type {
      /// @brief Touched
      Touched = 0,
      /// @brief Released
      Released,
      None
    };
  };

} /* window */
} /* hx3d */

#endif /* HX3D_WINDOW_EVENTS */
