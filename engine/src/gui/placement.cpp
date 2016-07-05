/*
    GUI placement.

    Copyright (C) 2016 Denis BOURGE

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

#include "hx3d/gui/placement.hpp"

namespace hx3d {
namespace gui {

Placement::Placement(const Pointer<Widget>& widget) {
  _widget = widget;
}

Pointer<Widget> Placement::apply() {
  _widget->_transform.position.x = _position.x;
  _widget->_transform.position.y = _position.y;
  _widget->_transform.size.x = _size.x;
  _widget->_transform.size.y = _size.y;

  return _widget;
}

} /* gui */
} /* hx3d */
