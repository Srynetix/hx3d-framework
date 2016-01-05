/*
    Tween sequence.
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

#ifndef HX3D_TWEENS_SEQUENCE
#define HX3D_TWEENS_SEQUENCE

#include "hx3d/math/interpolation.hpp"

#include "hx3d/tweens/tween.hpp"
#include "hx3d/tweens/delay.hpp"
#include "hx3d/tweens/callback.hpp"

#include "hx3d/utils/ptr.hpp"

#include <queue>

namespace hx3d {
namespace tweens {

/**
@brief Sequential suite of tweens
*/
class Sequence: public BaseTween {
public:
  Sequence();

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
  @brief Create a delay tween.

  @param delay Delay as seconds
  */
  void addDelay(const float delay);

  /**
  @brief Create a callback tween.

  @param func Function
  */
  void addCallback(std::function<void()> func);

  /**
  @brief Add an existing tween.

  @param tween Base Tween (Ptr)
  */
  void add(const Ptr<BaseTween>& tween);

  virtual void update(const float delta) override;

private:
  /// @brief Tweens
  std::queue<Ptr<BaseTween>> tweens;
};

} /* math */
} /* hx3d */

#include "hx3d/tweens/_inline/sequence.inl.hpp"

#endif
