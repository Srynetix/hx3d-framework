/*
    Callback Timer.
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

#include "hx3d/utils/callback_timer.hpp"

namespace hx3d {

CallbackTimer::CallbackTimer():
  _timer(-1) {}

CallbackTimer::CallbackTimer(float delay, std::function<void()> function):
  _timer(delay), _function(function) {}

void CallbackTimer::initialize(float delay, std::function<void()> function) {
  _timer.initialize(delay);
  _function = function;
}

long CallbackTimer::remaining() {
  return _timer.remaining();
}

void CallbackTimer::update() {
  if (_timer.isEnded()) {
    if (_function)
      _function();
  }
}

void CallbackTimer::reset() {
  _timer.reset();
}

} /* hx3d */
