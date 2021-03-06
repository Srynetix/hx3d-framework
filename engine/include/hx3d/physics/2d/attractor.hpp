/*
    Physical attractor.
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

#ifndef HX3D_PHYSICS_2D_ATTRACTOR
#define HX3D_PHYSICS_2D_ATTRACTOR

#include "hx3d/utils/ptr.hpp"

#include "hx3d/physics/2d/collider.hpp"

namespace hx3d {
namespace physics2d {

/**
@brief Physical gravity attractor
*/
struct Attractor {

  /**
  @brief Attractor type
  */
  enum class Type {
    /// @brief Global attractor
    Global = 1,
    /// @brief Zone attractor
    Zone,
    /// @brief Point attractor
    Point
  };

  /// @brief Attractor type
  Type type;
  /// @brief Attractor priority
  unsigned int priority;

  /**
  @brief Create an attractor

  @param type Attractor type
  */
  Attractor(Type type);

  /**
  @brief Check if a collider overlaps the attractor

  @param collider Collider (Ptr)

  @return True/False
  */
  virtual bool overlaps(const Ptr<Collider>& collider) = 0;

  /**
  @brief Compute the gravity force on a collider

  @param collider Collider (Ptr)
  @param dt       Delta time
  */
  virtual void computeForce(const Ptr<Collider>& collider, const float dt) = 0;

  /**
  @brief Defines the current attractor on a collider

  @param collider   Collider (Ptr)
  @param attractor  Attractor (Ptr)
  @param dt         Delta time
  */
  static void setCurrentAttractor(const Ptr<Collider>& collider, const Ptr<Attractor>& attractor, const float dt);

  /**
  @brief Apply an attractor force on a collider.

  @param collider   Collider (Ptr)
  @param attractor  Attractor (Ptr)
  @param dt         Delta time
  */
  static void applyForce(const Ptr<Collider>& collider, const Ptr<Attractor>& attractor, const float dt);
};

} /* physics2d */
} /* hx3d */

#endif
