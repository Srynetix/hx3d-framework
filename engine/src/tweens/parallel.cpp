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

#include "hx3d/tweens/parallel.hpp"

#include "hx3d/tweens/callback.hpp"

namespace hx3d {
namespace tweens {

Parallel::Parallel(bool infinite): BaseTween(infinite) {}

void Parallel::add(const Ptr<BaseTween>& tween) {
  tweens.push_back(tween);
}

void Parallel::addRepeatingCallback(std::function<void()> func, const float duration) {
  Ptr<BaseTween> tween = Make<Callback>(func, duration);
  tweens.push_back(tween);
}

void Parallel::reset() {
  for (auto i = tweens.begin(); i != tweens.end(); ++i) {
    const Ptr<BaseTween>& tween = *i;
    tween->reset();
  }
}

void Parallel::update(const float delta) {
  if (_ended)
    return;

  bool all_ended = true;
  for (auto i = tweens.begin(); i != tweens.end(); ++i) {
    const Ptr<BaseTween>& tween = *i;

    if (!tween->hasEnded()) {
      all_ended = false;
      tween->update(delta);
    }
  }

  if (all_ended) {
    if (_infinite) {
      reset();
    } else {
      _ended = true;
    }
  }
}

} /* tweens */
} /* hx3d */
