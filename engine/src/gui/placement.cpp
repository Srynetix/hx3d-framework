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
#include "hx3d/gui/widget.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"

namespace hx3d {
namespace gui {

Placement::Placement(const Pointer<Widget>& widget) {
  _widget = widget;
}

Pointer<Widget> Placement::apply() {
  if (_func) {
    _func(*this);
  }

  _widget->setPosition(_position.x, _position.y);
  _widget->setSize(_size.x, _size.y);

  return _widget;
}

Placement Placement::None(const Pointer<Widget>& widget) {
  Placement pla(widget);
  pla._func = [widget](Placement& pl){
    pl._size = widget->getSize();
    pl._position = widget->getPosition();
  };

  return pla;
}

Placement Placement::Fill(const Pointer<Widget>& widget) {
  Placement pla(widget);
  pla._func = [widget](Placement& pl){
    if (widget->_parent) {
      pl._size = widget->_parent->getSize();
      pl._position = widget->_parent->getPosition();
    }

    else {
      pl._size = Core::App()->getSize();
      pl._position = Core::App()->getSize() / 2;
    }
  };

  return pla;
}

Placement Placement::Relative(const Pointer<Widget>& widget, glm::vec2 relativePos, glm::vec2 relativeSize) {
  Placement pla(widget);
  pla._func = [widget,relativePos,relativeSize](Placement& pl) {
    if (widget->_parent) {
      auto trans = widget->_parent;
      glm::vec2 base_pos = {
        trans->getPosition().x - trans->getSize().x / 2,
        trans->getPosition().y - trans->getSize().y / 2
      };

      pl._position = {
        base_pos.x + trans->getSize().x * relativePos.x,
        base_pos.y + trans->getSize().y * relativePos.y
      };

      pl._size = {
        trans->getSize().x * relativeSize.x,
        trans->getSize().y * relativeSize.y
      };
    }

    else {
      pl._position = {Core::App()->getWidth() * relativePos.x, Core::App()->getHeight() * relativePos.y};
      pl._size = {Core::App()->getWidth() * relativeSize.x, Core::App()->getHeight() * relativeSize.y};
    }
  };

  return pla;
}

} /* gui */
} /* hx3d */
