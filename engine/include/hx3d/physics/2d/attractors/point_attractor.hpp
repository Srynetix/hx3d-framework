/*
    Point attractor.
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

#ifndef HX3D_PHYSICS_2D_ATTRACTORS_POINT_ATTRACTOR
#define HX3D_PHYSICS_2D_ATTRACTORS_POINT_ATTRACTOR

#include "hx3d/physics/2d/attractor.hpp"

namespace hx3d {
namespace physics2d {

/**
@brief Point attractor
*/
struct PointAttractor: public Attractor {

  PointAttractor();

  virtual bool overlaps(const Ptr<Collider>& collider) override;
  virtual void computeForce(const Ptr<Collider>& collider, const float dt) override;

  /// @brief Point position
  glm::vec2 position;
  /// @brief Point velocity
  glm::vec2 velocity;
  /// @brief Point radius
  float radius;
};

} /* physics2d */
} /* hx3d */

#endif
