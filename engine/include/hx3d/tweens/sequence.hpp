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

class Sequence: public BaseTween {
public:
  Sequence();

  template <class T>
  void addTween(T& mod, T to, float duration, math::Interpolation interp);
  void addDelay(float delay);
  void addCallback(std::function<void()> func);
  void add(Ptr<BaseTween> tween);

  virtual void update(float delta) override;

  std::queue<Ptr<BaseTween>> tweens;
};

} /* math */
} /* hx3d */

#include "hx3d/tweens/_inline/sequence.inl.hpp"

#endif
