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

#ifndef HX3D_GRAPHICS_PARTICLES_PARTICLEMANAGER
#define HX3D_GRAPHICS_PARTICLES_PARTICLEMANAGER

#include "hx3d/graphics/particles/particle_emitter.hpp"

namespace hx3d {

class ParticleManager {
public:
  ParticleManager();

  /**
  Add an emitter.

  @param emitter Particle emitter
  */
  void addEmitter(const Ptr<ParticleEmitter>& emitter);

  /**
  Update the particle manager.

  @param delta Delta time
  */
  void update(const float delta);

  /**
  Draw the particles.

  @param batch Batch
  */
  void draw(Batch& batch);

private:
  std::vector<Ptr<ParticleEmitter>> emitters;
};

} /* hx3d */

#endif
