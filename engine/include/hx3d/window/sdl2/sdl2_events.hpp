/*
    SDL2 Events Implementation.
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

#ifndef HX3D_WINDOW_SDL2_SDL2EVENTS
#define HX3D_WINDOW_SDL2_SDL2EVENTS

#include "hx3d/window/event_manager.hpp"

namespace hx3d {
namespace window {

/**
@brief SDL2 event manager implementation
*/
class SDL2EventManager: public EventManager {

public:
  virtual void poll() override;
};

} /* window */
} /* hx3d */

#endif /* HX3D_WINDOW_SDL2_SDL2EVENTS */
