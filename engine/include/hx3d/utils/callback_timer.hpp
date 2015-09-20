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

#ifndef HX3D_UTILS_CALLBACKTIMER
#define HX3D_UTILS_CALLBACKTIMER

#include "hx3d/utils/timer.hpp"

#include <functional>

namespace hx3d {

class CallbackTimer {
public:
  /**
  Create an uninitialized callback timer.
  See @link#initialize.
  */
  CallbackTimer();

  /**
  Create a callback timer using a delay and a function.
  The delay is in milliseconds.

  @param delay    Timer delay
  @param function Callback
  */
  CallbackTimer(float delay, std::function<void()> function);

  /**
  Initialize the timer.
  The delay is in milliseconds.

  @param delay    Timer delay
  @param function Callback
  */
  void initialize(float delay, std::function<void()> function);

  /**
  Get the remaining time in milliseconds.

  @return Remaining time
  */
  long remaining();

  /**
  Reset the timer.
  */
  void reset();

  /**
  Update the timer.
  */
  void update(float delta);

private:
  Timer _timer;
  std::function<void()> _function;
};

} /* hx3d */

#endif
