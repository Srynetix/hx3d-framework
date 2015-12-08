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

#ifndef HX3D_GRAPHICS_PARTICLES_PARTICLEEMITTER
#define HX3D_GRAPHICS_PARTICLES_PARTICLEEMITTER

#include "hx3d/graphics/particles/particle.hpp"
#include "hx3d/utils/pool.hpp"

namespace hx3d {

class ParticleEmitter {
public:

  /**
  Construct an emitter with a max particle number.

  @param maxParticles Max particle count
  */
  ParticleEmitter(const unsigned int maxParticles);

  /**
  Emit particles.

  @param qty Quantity
  */
  void emit(const unsigned int qty);

  /**
  Update the emitter.

  @param delta Delta time
  */
  void update(const float delta);

  /**
  Draw the particles.

  @param batch Batch
  */
  void draw(Batch& batch);

  /**
  Set the emitter texture.

  @param texture Texture (Ptr)
  */
  void setTexture(const Ptr<Texture>& texture);

  /**
  Get the active particle count.

  @return Active particle count
  */
  unsigned int getParticleCount();

  glm::vec3 position;
  glm::vec3 emitter_size;
  glm::vec3 particle_size;
  glm::vec3 gravity;
  glm::vec3 velocity;
  float rotationSpeed;
  float life;

private:
  /**
  Emit one particle.
  */
  void emitOne();

  Pool<Particle> particles;
  Ptr<Texture> texture;
};

} /* hx3d */

#endif
