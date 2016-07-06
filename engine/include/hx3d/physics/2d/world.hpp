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

#pragma once

#include "hx3d/physics/2d/manifold.hpp"
#include "hx3d/physics/2d/collision_matrix.hpp"

#include <set>

namespace hx3d {

namespace graphics {
  class Batch;
}

/**
@brief 2D physics components
*/
namespace physics2d {

class Attractor;
class CollisionListener;
class GlobalAttractor;

/**
@brief Physical world. Manages colliders and attractors.
*/
class World {
  HX3D_PTR(World)

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
  void addAttractor(const Pointer<Attractor>& attractor);

  /**
  @brief Add a collision listener

  @param listener Collision listener
  */
  void addListener(const Pointer<CollisionListener>& listener);

  /**
  @brief Add a collider

  @param collider Collider
  */
  void addCollider(const Pointer<Collider>& collider);

  /**
  @brief Remove a collider

  @param collider Collider
  */
  void removeCollider(const Pointer<Collider>& collider);

  /**
  @brief Step the physical simulation

  @param dt Delta time
  */
  void step(float dt = 1.f/60.f);

  /**
  @brief Render a debug view of the physical simulation

  @param batch Batch
  */
  void render(const Pointer<graphics::Batch>& batch);

  /**
  @brief Get the physical ratio

  @return Physical ratio
  */
  float getPhysRatio() const;

  /**
  @brief Get the global attractor

  @return Global attractor
  */
  const Pointer<GlobalAttractor> getGlobalGravity();

  /**
  @brief Get the collision matrix

  @return Collision matrix
  */
  CollisionMatrix& getCollisionMatrix();

private:
  /// @brief Iterations
  unsigned int _iterations;
  /// @brief Physical ratio
  float _physRatio;

  /// @brief Attractors
  std::vector<Pointer<Attractor>> _attractors;
  /// @brief Colliders
  std::vector<Pointer<Collider>> _colliders;
  /// @brief Collision listeners
  std::vector<Pointer<CollisionListener>> _listeners;
  /// @brief Contacts
  std::vector<Manifold> _contacts;

  /// @brief Manifolds in contact
  std::set<Manifold> _inContact;
  /// @brief Manifolds in previous contact
  std::set<Manifold> _inPrevContact;

  CollisionMatrix _collisionMatrix;

  /**
  @brief Integrate forces on the colliders

  @param c Collider (Ptr)
  @param dt Delta time
  */
  void integrateForces(const Pointer<Collider>& c, float dt);

  /**
  @brief Integrate velocity on the colliders

  @param c Collider (Ptr)
  @param dt Delta time
  */
  void integrateVelocity(const Pointer<Collider>& c, float dt);

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
