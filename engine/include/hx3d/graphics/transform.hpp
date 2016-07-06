/*
    Transform.
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

#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>

#include <glm/gtx/transform.hpp>

namespace hx3d {
namespace graphics {

/**
@brief 2D/3D transform.
*/
class Transform {

public:
  Transform();
  Transform& operator=(const Transform& transform);

  /**
  @brief Build the model matrix using the position, scale, size and rotation.

  @return Matrix (mat4)
  */
  glm::mat4 compute();

  /**
  @brief Add a transform to another.

  In use for parent/child transform calculation.

  @param transform Other transform
  @return Current transform
  */
  Transform add(const Transform& transform);

  /**
  @brief Get the real size (size * scale).

  @return Real size
  */
  glm::vec3 realSize();

  /**
  @brief Check a point in the transform

  @param point 2D point

  @return True/False
  */
  bool contains(glm::vec2 point);

  /**
  @brief Show the transform information. (Debug)
  */
  void show();

  /// @brief Position
  glm::vec3 position;
  /// @brief Scale
  glm::vec3 scale;
  /// @brief Size
  glm::vec3 size;
  /// @brief Rotation
  glm::vec3 rotation;
};

} /* graphics */
} /* hx3d */
