/*
    Physical world.

    Copyright (C) 2013 Randy Gaul http://RandyGaul.net
    Copyright (C) 2015 Denis BOURGE

    Thanks to RandyGaul for his tutorial and source.
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
#include "hx3d/physics/2d/collision_listener.hpp"

#include "hx3d/graphics/base_batch.hpp"

#include <set>

namespace hx3d {

/**
@brief 2D physics components
*/
namespace physics2d {

/**
@brief Physical world. Manages colliders and attractors.
*/
class World {
public:
  /**
  @brief Create a world with a global gravity, iterations and the physical ratio.

  @param globalGravity  Main global gravity
  @param iterations     Iterations
  @param physRatio      Physical ratio
  */
  World(const glm::vec2 globalGravity = {0, -9.81}, const unsigned int iterations = 10, const float physRatio = 10.f);

  /**
  @brief Add an attractor

  @param attractor Attractor
  */
  void addAttractor(const Ptr<Attractor>& attractor);

  /**
  @brief Add a collision listener

  @param listener Collision listener
  */
  void addListener(const Ptr<CollisionListener>& listener);

  /**
  @brief Add a collider

  @param collider Collider
  */
  void addCollider(const Ptr<Collider>& collider);

  /**
  @brief Remove a collider

  @param collider Collider
  */
  void removeCollider(const Ptr<Collider>& collider);

  /**
  @brief Step the physical simulation

  @param dt Delta time
  */
  void step(float dt = 1.f/60.f);

  /**
  @brief Render a debug view of the physical simulation

  @param batch Batch
  */
  void render(graphics::BaseBatch& batch);

  /**
  @brief Get the physical ratio

  @return Physical ratio
  */
  float getPhysRatio() const;

  /**
  @brief Get the global attractor

  @return Global attractor
  */
  const Ptr<GlobalAttractor> getGlobalGravity();

private:
  /// @brief Iterations
  unsigned int _iterations;
  /// @brief Physical ratio
  float _physRatio;

  /// @brief Attractors
  std::vector<Ptr<Attractor>> _attractors;
  /// @brief Colliders
  std::vector<Ptr<Collider>> _colliders;
  /// @brief Collision listeners
  std::vector<Ptr<CollisionListener>> _listeners;
  /// @brief Contacts
  std::vector<Manifold> _contacts;

  /// @brief Manifolds in contact
  std::set<Manifold> _inContact;
  /// @brief Manifolds in previous contact
  std::set<Manifold> _inPrevContact;

  /**
  @brief Integrate forces on the colliders

  @param c Collider (Ptr)
  @param dt Delta time
  */
  void integrateForces(const Ptr<Collider>& c, float dt);

  /**
  @brief Integrate velocity on the colliders

  @param c Collider (Ptr)
  @param dt Delta time
  */
  void integrateVelocity(const Ptr<Collider>& c, float dt);

  /**
  @brief Check if a previous contact exists

  @param manifold Current contact

  @return True/False
  */
  bool prevContactExists(Manifold& m);

  /**
  @brief Check the old contacts
  */
  void checkOldContacts();
};

} /* physics2d */
} /* hx3d */

#endif
