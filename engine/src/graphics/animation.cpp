/*
    Animated sprite.
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

#include "hx3d/graphics/animation.hpp"

namespace hx3d {
namespace graphics {

Animation::Animation() {}
Animation::Animation(Pointer<TextureAtlas> atlas, std::vector<std::string> frames, float speed) {
  initialize(atlas, frames, speed);
}

void Animation::initialize(Pointer<TextureAtlas> atlas, std::vector<std::string> frames, float speed) {
  _atlas = atlas;
  _currentTime = 0;
  _frames = frames;
  _delay = speed;

  setTexture(_atlas->getRegion(_frames[0]));
}

void Animation::update(float delta) {
  _currentTime += delta;
  if (_currentTime >= _delay) {
    _currentTime -= _delay;
  }

  unsigned int framesQty = _frames.size();
  float limit = _delay / framesQty;
  unsigned int currentFrame = (unsigned int)(_currentTime / limit);
  setTexture(_atlas->getRegion(_frames[currentFrame]));
}

} /* graphics */
} /* hx3d */
