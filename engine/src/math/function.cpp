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
    : _init(init), _speed(speed), _t(init), _enabled(true), _func(func)
  {}

Function::Function():
  _init(0), _speed(0), _t(0), _enabled(false), _func(nullptr)
  {}

void Function::disable() {
  _enabled = false;
}

void Function::enable() {
  _enabled = true;
}

bool Function::isEnabled() {
  return _enabled;
}

void Function::reset() {
  _t = _init;
}

void Function::setInit(float init) {
  _init = init;
}

glm::vec2 Function::sample() {
  if (_enabled) {
    glm::vec2 coord(0, 0);
    _func(coord.x, coord.y, _t);

    return coord;
  }

  return glm::vec2(0, 0);
}

void Function::step() {
  _t += _speed;
}

} /* math */
} /* hx3d */
