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

#include "hx3d/tweens/sequence.hpp"
#include "hx3d/tweens/callback.hpp"
#include "hx3d/tweens/delay.hpp"

namespace hx3d {
namespace tweens {

Sequence::Sequence(bool infinite): BaseTween(infinite) {}

void Sequence::addDelay(const float delay) {
  Pointer<BaseTween> tween = Make<Delay>(delay);
  tweens.push_back(tween);
}

void Sequence::addCallback(std::function<void()> func) {
  Pointer<BaseTween> tween = Make<Callback>(func);
  tweens.push_back(tween);
}

void Sequence::add(const Pointer<BaseTween>& tween) {
  tweens.push_back(tween);
}

void Sequence::reset() {
  for (auto i = tweens.begin(); i != tweens.end(); ++i) {
    const Pointer<BaseTween>& tween = *i;
    tween->reset();
  }
}

void Sequence::update(const float delta) {
  if (_ended)
    return;

  bool all_ended = true;
  for (auto i = tweens.begin(); i != tweens.end(); ++i) {
    const Pointer<BaseTween>& tween = *i;

    if (!tween->hasEnded()) {
      all_ended = false;
      tween->update(delta);
      break;
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
