/*
    Simple math function.
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

#include "hx3d/math/function.hpp"

namespace hx3d {
namespace math {

Function::Function(float init, float speed, std::function<void(float&, float&, float)> func)
    : _init(init), _speed(speed), _t(init), _func(func)
  {}

void Function::reset() {
  _t = _init;
}

glm::vec2 Function::sample() {
  glm::vec2 coord(0, 0);
  _func(coord.x, coord.y, _t);

  return coord;
}

void Function::step() {
  _t += _speed;
}

} /* math */
} /* hx3d */
