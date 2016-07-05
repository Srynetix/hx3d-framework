/*
    GUI Placement.
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

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"

namespace hx3d {
namespace gui {

template <class W>
Pointer<W> Placement::None(const Pointer<Widget>& widget) {
  Placement pl(widget);
  pl._size = {widget->_transform.size.x, widget->_transform.size.y};
  pl._position = {widget->_transform.position.x, widget->_transform.position.y};

  return std::dynamic_pointer_cast<W>(pl.apply());
}

template <class W>
Pointer<W> Placement::Fill(const Pointer<Widget>& widget) {
  Placement pl(widget);

  if (widget->_parent) {
    pl._size = {widget->_parent->_transform.size.x, widget->_parent->_transform.size.y};
    pl._position = {widget->_parent->_transform.position.x, widget->_parent->_transform.position.y};
  }

  else {
    pl._size = Core::App()->getSize();
    pl._position = Core::App()->getSize() / 2;
  }

  return std::dynamic_pointer_cast<W>(pl.apply());
}

template <class W>
Pointer<W> Placement::Relative(const Pointer<Widget>& widget, glm::vec2 relativePos, glm::vec2 relativeSize) {
  Placement pl(widget);
  if (widget->_parent) {
    auto trans = widget->_parent->_transform;

    pl._position = {trans.size.x * relativePos.x, trans.size.y * relativePos.y};
    pl._size = {trans.size.x * relativeSize.x, trans.size.y * relativeSize.y};
  }

  else {
    pl._position = {Core::App()->getWidth() * relativePos.x, Core::App()->getHeight() * relativePos.y};
    pl._size = {Core::App()->getWidth() * relativeSize.x, Core::App()->getHeight() * relativeSize.y};
  }

  return std::dynamic_pointer_cast<W>(pl.apply());
}

} /* gui */
} /* hx3d */
