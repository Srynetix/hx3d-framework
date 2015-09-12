/*
    Timer.
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

#include "hx3d/utils/timer.hpp"

#include <algorithm>

namespace hx3d {

Timer::Timer():
  Timer(-1) {}

Timer::Timer(long delay):
  _delay(delay), _begin(std::chrono::system_clock::now()), _alreadyEnded(false)
{}

void Timer::initialize(long delay) {
  _delay = delay;
  reset();
}

void Timer::reset() {
  _begin = std::chrono::system_clock::now();
  _alreadyEnded = false;
}

long Timer::remaining() {
  if (_delay == -1)
    return 0xFF;

  std::chrono::system_clock::time_point point = std::chrono::system_clock::now();
  long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(point - _begin).count();

  return std::max(0L, _delay - elapsed);
}

bool Timer::hasEnded() {
  if (_alreadyEnded)
    return false;

  if (remaining() == 0) {
    _alreadyEnded = true;
    return true;
  }

  return false;
}

} /* hx3d */
