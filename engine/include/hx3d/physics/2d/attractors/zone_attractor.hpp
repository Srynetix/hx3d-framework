/*
    Zone attractor.
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

#ifndef HX3D_PHYSICS_2D_ATTRACTORS_ZONE_ATTRACTOR
#define HX3D_PHYSICS_2D_ATTRACTORS_ZONE_ATTRACTOR

#include "hx3d/physics/2d/attractor.hpp"

namespace hx3d {
namespace physics2d {

/**
@brief Zone attractor
*/
struct ZoneAttractor: public Attractor {

  /**
  @brief Zone attractor definition
  */
  struct Definition {
    Definition();

    /// @brief Physical ratio
    float unitCoef;

    /// @brief Position
    glm::vec2 position;
    /// @brief Velocity
    glm::vec2 velocity;

    /// @brief Zone width
    float width;
    /// @brief Zone height
    float height;
  };

  /// @brief Zone position
  glm::vec2 position;
  /// @brief Zone velocity
  glm::vec2 velocity;
  /// @brief Zone width
  float width;
  /// @brief Zone height
  float height;

  /**
  @brief Create an empty zone attractor.
  */
  ZoneAttractor();
  /**
  @brief Create a zone attractor using a definition.

  @param def Definition
  */
  explicit ZoneAttractor(const Definition& def);

  /**
  @brief Use a definition on the zone attractor.

  @param def Definition
  */
  void useDefinition(const Definition& def);

  virtual bool overlaps(const Pointer<Collider>& collider) override;
  virtual void computeForce(const Pointer<Collider>& collider, const float dt) override;
};

} /* physics2d */
} /* hx3d */

#endif
