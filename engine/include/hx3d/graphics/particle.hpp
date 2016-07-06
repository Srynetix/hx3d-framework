/*
    Particle.
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

#pragma once

#include "hx3d/graphics/color.hpp"

#include "hx3d/utils/poolable.hpp"
#include "hx3d/utils/ptr.hpp"

#include <glm/vec3.hpp>

namespace hx3d {
namespace graphics {

class Texture;
class Sprite;
class Batch;

/**
@brief Poolable 2D/3D particle.
*/
class Particle: public Poolable {
public:
  Particle();

  /**
  @brief Set the texture.

  @param texture Texture (Ptr)
  */
  void setTexture(const Pointer<Texture>& texture);

  /**
  @brief Update the particle.

  @param delta Delta time
  */
  void update(const float delta);

  /**
  @brief Draw the particle.

  @param batch Batch
  */
  void draw(const Pointer<Batch>& batch);

  virtual void reset() override;

  /////////////////

private:
  /// @brief Position
  glm::vec3 position;
  /// @brief Size
  glm::vec3 size;
  /// @brief Velocity
  glm::vec3 velocity;
  /// @brief Gravity
  glm::vec3 gravity;
  /// @brief Z-Rotation
  float rotation;
  /// @brief Z-Rotation speed
  float rotationSpeed;

  /// @brief Base life
  float baseLife;
  /// @brief Current life
  float life;
  /// @brief Color
  Color color;

  /// @brief Internal sprite
  Pointer<Sprite> sprite;
  /// @brief Is the particle dead ?
  bool dead;

  friend class ParticleEmitter;
};

} /* graphics */
} /* hx3d */
