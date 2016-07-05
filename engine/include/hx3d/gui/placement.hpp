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

#pragma once

#include "hx3d/gui/widget.hpp"

namespace hx3d {
namespace gui {

class Placement {

public:
  Placement(const Pointer<Widget>& widget);
  Pointer<Widget> apply();

  template <class W>
  static Pointer<W> None(const Pointer<Widget>& widget);
  template <class W>
  static Pointer<W> Fill(const Pointer<Widget>& widget);
  template <class W>
  static Pointer<W> Relative(const Pointer<Widget>& widget, glm::vec2 relativePos, glm::vec2 relativeSize);

private:
  Pointer<Widget> _widget;
  glm::vec2 _size;
  glm::vec2 _position;
};

} /* gui */
} /* hx3d */

#include "hx3d/gui/_inline/placement.inl.hpp"
