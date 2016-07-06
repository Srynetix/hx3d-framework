/*
    Delay tween.
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

#include "hx3d/tweens/base_tween.hpp"

namespace hx3d {
namespace tweens {

/**
@brief Delay tween.

Make a pause in a sequence.
*/
class Delay: public BaseTween {
public:
  /**
  @brief Create a delay tween using a specified time in seconds.

  @param delayAsSeconds Delay as seconds
  */
  Delay(const float delayAsSeconds);

  virtual void reset() override;
  virtual void update(const float delta) override;

private:
  /// @brief Delay
  float _delay;
  /// @brief Current time
  float _currentTime;
};

} /* tween */
} /* hx3d */
