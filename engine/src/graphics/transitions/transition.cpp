/*
    Screen transition.
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

#include "hx3d/graphics/transitions/transition.hpp"

#include "hx3d/graphics/sprite.hpp"

namespace hx3d {
namespace graphics {

Transition::Transition(window::Game* game) {
  _duration = 1.f;
  _currentTime = 0.f;
  _running = false;

  _game = game;

  _currentSprite = Make<Sprite>();
  _nextSprite = Make<Sprite>();
}

void Transition::start() {
  _currentTime = 0.f;
  _running = true;

  onStart();
}

void Transition::reset() {
  _currentTime = 0.f;
  _running = false;
}

void Transition::setDuration(float duration) {
  _duration = duration;
}

bool Transition::isFinished() const {
  return _running && _currentTime >= _duration;
}

bool Transition::isRunning() const {
  return _running;
}

void Transition::update(float delta) {
  if (_running) {
    _currentTime += delta;
    onUpdate(delta);
  }
}

void Transition::onDone() {}
void Transition::onStart() {}
void Transition::onUpdate(float delta) {}

} /* graphics */
} /* hx3d */
