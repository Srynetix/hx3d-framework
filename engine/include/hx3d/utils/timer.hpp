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

class Timer {

public:

  /**
  Create an uninitialized timer.
  See @link#initialize.
  */
  Timer();

  /**
  Create a timer with a delay as milliseconds.

  @param delay Delay
  */
  Timer(long delay);

  /**
  Initialize the timer with a delay.

  @param delay Delay
  */
  void initialize(long delay);

  /**
  Reset the timer.
  */
  void reset();

  /**
  Get the remaining time as milliseconds.
  
  @return milliseconds
  */
  long remaining();

  /**
  Test if the timer is ended.
  */
  bool isEnded();

private:
    long _delay;
    std::chrono::system_clock::time_point _begin;
    bool _alreadyEnded;
};

} /* hx3d */

#endif
