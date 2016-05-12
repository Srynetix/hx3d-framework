/*
    GUI system.
    Manage a GUI instance.

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

#ifndef HX3D_GUI_SYSTEM
#define HX3D_GUI_SYSTEM

#include "hx3d/gui/widget.hpp"

namespace hx3d {
namespace gui {

/**
@brief GUI system: GUI scene graph & event manager
*/
class System {

public:
  System();

  /**
  @brief Return the main system content.

  @return Widget (Ptr)
  */
  Pointer<Widget> getContent();

private:
  /// @brief Root
  Pointer<Widget> _content;
};

} /* gui */
} /* hx3d */

#endif
