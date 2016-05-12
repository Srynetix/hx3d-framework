/*
    Particle manager.
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

#include "hx3d/graphics/particle_manager.hpp"

namespace hx3d {
namespace graphics {

ParticleManager::ParticleManager()
{}

void ParticleManager::addEmitter(const Pointer<ParticleEmitter>& emitter) {
  emitters.push_back(emitter);
}

void ParticleManager::update(const float delta) {
  for (Pointer<ParticleEmitter>& emitter: emitters) {
    emitter->update(delta);
  }
}

void ParticleManager::draw(const Pointer<Batch>& batch) {

  glDisable(GL_DEPTH_TEST);

  for (Pointer<ParticleEmitter>& emitter: emitters) {
    emitter->draw(batch);
  }

  glEnable(GL_DEPTH_TEST);
}

} /* graphics */
} /* hx3d */
