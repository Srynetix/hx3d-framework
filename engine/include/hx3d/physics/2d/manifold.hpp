/*
    Contact manifold.
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

#ifndef HX3D_PHYSICS_2D_MANIFOLD
#define HX3D_PHYSICS_2D_MANIFOLD

#include "hx3d/physics/2d/colliders/polygon.hpp"
#include "hx3d/physics/2d/colliders/circle.hpp"

namespace hx3d {
namespace physics2d {

using namespace colliders;

/**
@brief Contact manifold definition
*/
class Manifold {
public:
  /// @brief First collider
  Ptr<Collider> a;
  /// @brief Second collider
  Ptr<Collider> b;

  /// @brief Penetration coefficient
  float penetration;

  /// @brief Is the contact disabled ?
  bool disabled;

  /// @brief Normal vector
  glm::vec2 normal;
  /// @brief Contact points
  std::vector<glm::vec2> contacts;

  /// @brief Mixed restitution (e)
  float mixedRestitution; // e
  /// @brief Mixed dynamic friction (df)
  float mixedDynamicFriction; // df
  /// @brief Mixed static friction (sf)
  float mixedStaticFriction; // sf

  ///////////

  /**
  @brief Create a manifold.

  @param a First collider
  @param b Second collider
  */
  Manifold(const Ptr<Collider>& a, const Ptr<Collider>& b);

  /**
  @brief Solve the contact
  */
  bool solve();

  /**
  @brief Initialize the manifold
  */
  void initialize();

  /**
  @brief Apply impulses to the colliders
  */
  void applyImpulse();

  /**
  @brief Do positional correction on the colliders
  */
  void positionalCorrection();

  /**
  @brief Do infinite mass correction on the colliders
  */
  void infiniteMassCorrection();

  friend bool operator<(const Manifold& m1, const Manifold& m2);
};

/**
@brief Compare two manifolds using their penetration coefficients.
*/
bool operator<(const Manifold& m1, const Manifold& m2);

} /* physics2d */
} /* hx3d */

#endif
