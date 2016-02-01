
/*
    Tween management.
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

#include "hx3d/tweens/tween_manager.hpp"

namespace hx3d {
namespace tweens {

TweenManager::TweenManager() {}

void TweenManager::add(const Ptr<BaseTween>& tween) {
  tweens.push_back(tween);
}

void TweenManager::update(const float delta) {
  for (auto i = tweens.begin(); i != tweens.end();) {
    const Ptr<BaseTween>& tween = *i;
    if (tween->hasEnded()) {
      tweens.erase(i);
    } else {
      tween->update(delta);
      ++i;
    }
  }
}

unsigned int TweenManager::getTweenCount() {
  return tweens.size();
}

void TweenManager::clear() {
  tweens.clear();
}

} /* tween */
} /* hx3d */
