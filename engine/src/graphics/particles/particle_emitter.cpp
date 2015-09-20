/*
    Particle emitter.
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

#include "hx3d/graphics/particles/particle_emitter.hpp"

#include "hx3d/math/random.hpp"

namespace hx3d {

ParticleEmitter::ParticleEmitter(unsigned int maxParticles):
  particles(maxParticles), texture(nullptr)
{}

void ParticleEmitter::emit(unsigned int qty) {
  for (unsigned int i = 0; i < qty; ++i) {
    emitOne();
  }
}

void ParticleEmitter::update(float delta) {
  const auto& working = particles.getWorking();

  for (auto i = working.begin(); i != working.end();) {
    const Ptr<Particle>& p = *i;
    if (p->dead) {
      particles.release(p);
    } else {
      p->update(delta);
      ++i;
    }
  }
}

void ParticleEmitter::draw(Batch& batch) {
  const auto& working = particles.getWorking();
  for (auto it = working.begin(); it != working.end(); ++it) {
    const Ptr<Particle> &p = *it;
    p->draw(batch);
  }
}

void ParticleEmitter::setTexture(Ptr<Texture> texture) {
  this->texture = texture;
}

unsigned int ParticleEmitter::getParticleCount() {
  return particles.getWorking().size();
}

////////////////////

void ParticleEmitter::emitOne() {
  Ptr<Particle> p = particles.take();
  if (!p) {
    return;
  }

  p->setTexture(texture);
  p->position.x = math::random(position.x - emitter_size.x / 2.f, position.x + emitter_size.x / 2.f);
  p->position.y = math::random(position.y - emitter_size.y / 2.f, position.y + emitter_size.y / 2.f);
  p->size.x = particle_size.x;
  p->size.y = particle_size.y;
  p->velocity.x = velocity.x;
  p->velocity.y = velocity.y;
  p->gravity.x = gravity.x;
  p->gravity.y = gravity.y;
  p->baseLife = p->life = life;
}

} /* hx3d */
