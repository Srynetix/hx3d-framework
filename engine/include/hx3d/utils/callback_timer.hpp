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

#pragma once

#include "hx3d/utils/timer.hpp"

#include <functional>

namespace hx3d {

/**
@brief Improved timer with callback execution
*/
class CallbackTimer {
public:
  /**
  @brief Create an uninitialized callback timer.

  See @link initialize @endlink.
  */
  CallbackTimer();

  /**
  @brief Create a callback timer using a delay and a function.
  The delay is in milliseconds.

  @param delay    Timer delay
  @param function Callback
  @param loop     Loop ?
  */
  CallbackTimer(float delay, std::function<void()> function, bool loop = false);

  /**
  @brief Initialize the timer.
  The delay is in milliseconds.

  @param delay    Timer delay
  @param function Callback
  @param loop     Loop ?
  */
  void initialize(float delay, std::function<void()> function, bool loop = false);

  /**
  @brief Get the remaining time in milliseconds.

  @return Remaining time
  */
  long remaining();

  /**
  @brief Reset the timer.
  */
  void reset();

  /**
  @brief Update the timer.
  */
  void update(float delta);

  /**
  @brief Did the timer ended ?

  @return True/False
  */
  bool hasEnded();

  /**
  @brief Is the timer looping ?

  @return True/False
  */
  bool isLooping();

private:
  Timer _timer;
  std::function<void()> _function;
  bool _loop;
};

} /* hx3d */
