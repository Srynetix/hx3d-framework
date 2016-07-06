/*
    Parallel tween sequence.
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

#include "hx3d/math/interpolation.hpp"
#include "hx3d/tweens/base_tween.hpp"
#include "hx3d/utils/ptr.hpp"

#include <vector>

namespace hx3d {
namespace tweens {

/**
@brief Parallel suite of tweens.
*/
class Parallel: public BaseTween {
public:
  /**
  Create a parallel tween.

  @param infinite Infinite ? (default: false)
  */
  Parallel(bool infinite = false);

  /**
  @brief Create a tween.

  @param mod      Base value to edit
  @param to       End value
  @param duration Duration
  @param interp   Interpolation function
  */
  template <class T>
  void addTween(T& mod, const T to, const float duration, const math::Interpolation interp);

  /**
  @brief Create a repeating callback.

  @param func     Function
  @param duration Duration
  */
  void addRepeatingCallback(std::function<void()> func, const float duration);

  /**
  @brief Add an existing tween.

  @param tween Base Tween (Ptr)
  */
  void add(const Pointer<BaseTween>& tween);

  virtual void reset() override;
  virtual void update(const float delta) override;

private:
  /// @brief Tweens
  std::vector<Pointer<BaseTween>> tweens;
};

} /* tween */
} /* hx3d */

#include "hx3d/tweens/_inline/parallel.inl.hpp"
