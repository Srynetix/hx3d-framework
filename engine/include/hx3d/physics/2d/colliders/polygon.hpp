/*
    2D polygon collider.
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

#include "hx3d/physics/2d/collider.hpp"

#include <vector>
#include <glm/mat2x2.hpp>
#include <hx3d/utils/reference.hpp>

namespace hx3d {
namespace physics2d {

/**
@brief Polygon or box shaped collider
*/
class Polygon: public Collider {
  HX3D_PTR_REF(Polygon)

public:
  
  /**
  @brief Create a polygon.

  @param colliderType Collider type
  */
  Polygon(const Type colliderType = Type::Dynamic);

  /**
  @brief Set the polygon points

  @param points Points
  */
  void setPoints(const std::vector<glm::vec2>& points);

  /**
  @brief Set the polygon points as a box.

  @param width  Box width
  @param height Box height
  */
  void setAsBox(const float width, const float height);

  /**
  @brief Get the support vector following a direction.

  @param dir Direction

  @return Support vector
  */
  glm::vec2 getSupport(glm::vec2 dir);

  virtual void setOrientation(float angle) override;
  virtual void computeMass(float density) override;

  /// @brief Vertex count
  unsigned int vertexCount;
  /// @brief Vertices
  std::vector<glm::vec2> vertices;
  /// @brief Normals
  std::vector<glm::vec2> normals;
  /// @brief Rotation matrix
  glm::mat2 u;
  /// @brief Is the polygon a box ?
  bool box;
};

} /* physics2d */
} /* hx3d */
