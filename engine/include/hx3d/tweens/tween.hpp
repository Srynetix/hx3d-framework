/*
    Regular tween.
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
@brief Templated tween definition
*/
template <class T>
class Tween: public BaseTween {
public:
  /**
  @brief Create a tween.

  @param mod      Base value to edit
  @param end      End value
  @param duration Duration
  @param interp   Interpolation function
  @param infinite Infinite ? (default: false)
  */
  Tween(T& mod, const T end, const float duration, const math::Interpolation interp, bool infinite = false);

  virtual void reset() override;
  virtual void update(const float delta) override;

private:
  /// @brief Value to edit
  T* mod;
  /// @brief Base value
  T base;
  /// @brief End value
  T end;

  /// @brief Duration
  float duration;
  /// @brief Current time
  float currentTime;
  /// @brief Interpolation function
  math::Interpolation interp;

  /// @brief Has done its first update ?
  bool _firstUpdate;
};

} /* tween */
} /* hx3d */

#include "hx3d/tweens/_inline/tween.inl.hpp"
