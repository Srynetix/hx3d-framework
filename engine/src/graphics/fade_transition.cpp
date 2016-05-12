/*
    Fade screen transition.
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

#include "hx3d/graphics/fade_transition.hpp"

#include "hx3d/graphics/sprite.hpp"
#include "hx3d/core/core.hpp"
#include "hx3d/window/game.hpp"
#include "hx3d/window/application.hpp"

namespace hx3d {
namespace graphics {

FadeTransition::FadeTransition(window::Game* game, Color color): Transition(game) {
  _color = color;
}

void FadeTransition::render(const Pointer<Batch>& batch, const Pointer<graphics::Framebuffer>& currentFB, const Pointer<graphics::Framebuffer>& nextFB) {
  Pointer<Sprite> spriteCurrent = Make<Sprite>();
  Pointer<Sprite> spriteNext = Make<Sprite>();
  spriteCurrent->setTexture(currentFB);
  spriteNext->setTexture(nextFB);

  auto world_size = Core::CurrentGame()->getSize();
  spriteCurrent->transform.position.x = world_size.x / 2;
  spriteCurrent->transform.position.y = world_size.y / 2;
  spriteCurrent->transform.rotation.z = glm::radians(180.f);

  spriteNext->transform.position.x = world_size.x / 2;
  spriteNext->transform.position.y = world_size.y / 2;
  spriteNext->transform.rotation.z = glm::radians(180.f);

  int alpha = (_currentTime / (_duration/2.f)) * 255;
  if (_currentTime > _duration / 2) {
    spriteNext->setTint(Color(255, 255, 255, alpha));
    Framebuffer::clear(_color);
    batch->begin();
    batch->draw(spriteNext);
    batch->end();
  }

  else {
    spriteCurrent->setTint(Color(255, 255, 255, 255 - alpha));
    Framebuffer::clear(_color);
    batch->begin();
    batch->draw(spriteCurrent);
    batch->end();
  }
}

void FadeTransition::onUpdate(float delta) {
}

void FadeTransition::onStart() {
}

void FadeTransition::onDone() {

}

} /* graphics */
} /* hx3d */
