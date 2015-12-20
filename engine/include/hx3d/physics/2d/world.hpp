/*
    Copyright (C) 2013 Randy Gaul http://RandyGaul.net
    Thanks to RandyGaul for his tutorial and source.

    Copyright (C) 2015 Denis BOURGE
    I've adapted RandyGaul's code to use with glm and my own code.
    Then I've added some features, as the multi-gravity system.

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

#ifndef HX3D_PHYSICS_2D_WORLD
#define HX3D_PHYSICS_2D_WORLD

#include "hx3d/physics/2d/manifold.hpp"
#include "hx3d/physics/2d/collider.hpp"

#include "hx3d/physics/2d/attractors/global_attractor.hpp"
#include "hx3d/physics/2d/attractors/point_attractor.hpp"
#include "hx3d/physics/2d/attractors/zone_attractor.hpp"

#include "hx3d/graphics/batch.hpp"

namespace hx3d {
namespace physics2d {

class World {
public:
  World(const glm::vec2 globalGravity = {0, -9.81}, const unsigned int iterations = 10, const float physRatio = 10.f);

  void addAttractor(const Ptr<Attractor>& attractor);
  void addCollider(const Ptr<Collider>& collider);
  void removeCollider(const Ptr<Collider>& collider);

  void step(float dt = 1.f/60.f);
  void render(Batch& batch);

  float getPhysRatio() const;

private:
  unsigned int _iterations;
  float _physRatio;

  std::vector<Ptr<Attractor>> _attractors;
  std::vector<Ptr<Collider>> _colliders;
  std::vector<Manifold> _contacts;

  void integrateForces(const Ptr<Collider>& c, float dt);
  void integrateVelocity(const Ptr<Collider>& c, float dt);
};

}
}

#endif
