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

} /* hx3d */

#endif /* HX3D_WINDOW_EVENTS */
