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

#ifndef HX3D_UTILS_TIMER
#define HX3D_UTILS_TIMER

#include <chrono>

namespace hx3d {

/**
@brief Simple timer.
*/
class Timer {

public:

  /**
  @brief Create an uninitialized timer.
  See @link initialize @endlink.
  */
  Timer();

  /**
  @brief Create a timer with a delay as milliseconds.

  @param delay Delay
  @param loop  Loop ?
  */
  Timer(long delay, bool loop = false);

  /**
  @brief Initialize the timer with a delay.

  @param delay Delay
  @param loop  Loop ?
  */
  void initialize(long delay, bool loop = false);

  /**
  @brief Reset the timer.
  */
  void reset();

  /**
  @brief Get the remaining time as milliseconds.

  @return milliseconds
  */
  long remaining();

  /**
  @brief Test if the timer has ended.

  @return True/False
  */
  bool hasEnded();

  /**
  @brief Update the timer.
  */
  void update(float delta);

  /**
  @brief Is the timer looping ?

  @return True/False
  */
  bool isLooping();

private:

  /// @brief Timer delay
  long _delay;
  /// @brief Time elapsed
  float _elapsed;
  /// @brief Has already ended ?
  bool _alreadyEnded;
  /// @brief Do loop ?
  bool _loop;
};

} /* hx3d */

#endif
