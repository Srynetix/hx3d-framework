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

#ifndef HX3D_GRAPHICS_PARTICLES_PARTICLE
#define HX3D_GRAPHICS_PARTICLES_PARTICLE

#include "hx3d/utils/poolable.hpp"
#include "hx3d/utils/ptr.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/batch.hpp"

namespace hx3d {

class Particle: public Poolable {
public:
  Particle();

  /**
  Set the texture.

  @param texture Texture (Ptr)
  */
  void setTexture(Ptr<Texture> texture);

  /**
  Update the particle.

  @param delta Delta time
  */
  void update(float delta);

  /**
  Draw the particle.

  @param batch Batch
  */
  void draw(Batch& batch);

  virtual void reset() override;

  /////////////////

private:
  glm::vec3 position;
  glm::vec3 size;
  glm::vec3 velocity;
  glm::vec3 gravity;
  float rotation;

  float baseLife;
  float life;
  Color color;

  Sprite sprite;
  bool dead;

  friend class ParticleEmitter;
};

} /* hx3d */

#endif
