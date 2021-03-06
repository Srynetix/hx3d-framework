/*
    Callback tween.
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

#include "hx3d/tweens/callback.hpp"

namespace hx3d {
namespace tweens {

Callback::Callback(std::function<void()> func):
  Callback(func, 0)
{}

Callback::Callback(std::function<void()> func, const float duration):
  BaseTween(false), _func(func), _delay(duration)
{}

void Callback::reset() {
  _ended = false;
  _currentTime = 0;
}

void Callback::update(const float delta) {
  if (_ended)
    return;

  _func();

  _currentTime += delta;
  if (_currentTime > _delay)
    _ended = true;
}

} /* tweens */
} /* hx3d */
