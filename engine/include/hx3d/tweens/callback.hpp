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

#pragma once

#include "hx3d/tweens/base_tween.hpp"

#include <functional>

namespace hx3d {
namespace tweens {

/**
@brief Callback tween.

Execute a callback at the end of the tween.
*/
class Callback: public BaseTween {
public:
  /**
  @brief Create a callback tween using a function.

  @param func Function
  */
  Callback(std::function<void()> func);

  /**
  @brief Create a callback tween usign a function and a duration.

  @param func     Function
  @param duration Duration
  */
  Callback(std::function<void()> func, const float duration);

  virtual void reset() override;
  virtual void update(const float delta) override;

private:
  /// @brief Function
  std::function<void()> _func;
  /// @brief Delay
  float _delay;
  /// @brief Current time
  float _currentTime;
};

} /* tween */
} /* hx3d */
