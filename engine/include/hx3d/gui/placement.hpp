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

#include "hx3d/utils/ptr.hpp"
#include <glm/vec2.hpp>
#include <functional>

namespace hx3d {
namespace gui {

class Widget;

class Placement {

public:
  Placement(const Pointer<Widget>& widget);
  Pointer<Widget> apply();

  static Placement None(const Pointer<Widget>& widget);
  static Placement Fill(const Pointer<Widget>& widget);
  static Placement Relative(const Pointer<Widget>& widget, glm::vec2 relativePos, glm::vec2 relativeSize);

  friend class Container;

private:
  Pointer<Widget> _widget;
  glm::vec2 _size;
  glm::vec2 _position;

  std::function<void(Placement&)> _func;
};

} /* gui */
} /* hx3d */
