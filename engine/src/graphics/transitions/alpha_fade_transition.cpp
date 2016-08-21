/*
    Alpha fade screen transition.
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

    TODO: FIX !
*/

#include "hx3d/graphics/transitions/alpha_fade_transition.hpp"

#include "hx3d/core/core.hpp"

#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/framebuffer.hpp"
#include "hx3d/graphics/batches/batch.hpp"

#include "hx3d/window/game.hpp"
#include "hx3d/window/application.hpp"

namespace hx3d {
namespace graphics {

AlphaFadeTransition::AlphaFadeTransition(window::Game* game): Transition(game) {}

void AlphaFadeTransition::render(const Pointer<Batch>& batch, const Pointer<Framebuffer>& currentFB, const Pointer<Framebuffer>& nextFB) {
  _currentSprite->setTexture(currentFB);
  _nextSprite->setTexture(nextFB);

  auto world_size = Core::CurrentGame()->getSize();
  _currentSprite->setPosition(world_size.x / 2, world_size.y / 2);
  _currentSprite->setRotation(glm::radians(180.f));

  _nextSprite->setPosition(world_size.x / 2, world_size.y / 2);
  _nextSprite->setRotation(glm::radians(180.f));

  // int alpha = (_currentTime / _duration) * 255;
  _nextSprite->setTint(Color(255, 255, 255, 255));
  _currentSprite->setTint(Color(255, 255, 255, 255));

  Framebuffer::clear(Color::Black);
  batch->begin();
  batch->draw(_nextSprite);
  batch->draw(_currentSprite);
  batch->end();
}

void AlphaFadeTransition::onUpdate(float delta) {
}

void AlphaFadeTransition::onStart() {
}

void AlphaFadeTransition::onDone() {

}

} /* graphics */
} /* hx3d */
