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

#ifndef HX3D_GRAPHICS_PARTICLEEMITTER
#define HX3D_GRAPHICS_PARTICLEEMITTER

#include "hx3d/graphics/particle.hpp"
#include "hx3d/utils/pool.hpp"

/**
TODO: Create a particle batch
*/

namespace hx3d {
namespace graphics {

/**
@brief Emit particles with parameters
*/
class ParticleEmitter {
public:

  /**
  @brief Construct an emitter with a max particle number.

  @param maxParticles Max particle count
  */
  ParticleEmitter(const unsigned int maxParticles);

  /**
  @brief Emit particles.

  @param qty Quantity
  */
  void emit(const unsigned int qty);

  /**
  @brief Update the emitter.

  @param delta Delta time
  */
  void update(const float delta);

  /**
  @brief Draw the particles.

  @param batch Batch
  */
  void draw(Batch& batch);

  /**
  @brief Set the emitter texture.

  @param texture Texture (Ptr)
  */
  void setTexture(const Ptr<Texture>& texture);

  /**
  @brief Get the active particle count.

  @return Active particle count
  */
  unsigned int getParticleCount();

  /// @brief Emitter position
  glm::vec3 position;
  /// @brief Emitter size
  glm::vec3 emitter_size;
  /// @brief Particles size
  glm::vec3 particle_size;
  /// @brief Particles gravity
  glm::vec3 gravity;
  /// @brief Particles velocity
  glm::vec3 velocity;
  /// @brief Particles Z-rotation speed
  float rotationSpeed;
  /// @brief Particles life
  float life;

private:
  /**
  @brief Emit one particle.
  */
  void emitOne();

  /// @brief Particles pool
  Pool<Particle> particles;

  /// @brief Particles texture
  Ptr<Texture> texture;
};

} /* graphics */
} /* hx3d */

#endif
