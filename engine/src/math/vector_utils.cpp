/*
    Vector helper methods.
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

#include "hx3d/math/vector_utils.hpp"

#include <glm/gtx/rotate_vector.hpp>

namespace hx3d {
namespace math {

glm::vec3 rotate(glm::vec3 vector, float angle, glm::vec3 axis) {
  glm::vec3 ret(vector);

  if (axis.x != 0)
    ret = glm::rotateX(ret, angle);
  if (axis.y != 0)
    ret = glm::rotateY(ret, angle);
  if (axis.z != 0)
    ret = glm::rotateZ(ret, angle);

  return ret;
}

glm::vec2 cross(float v, glm::vec2 vec) {
  return glm::vec2(-v * vec.y, v * vec.x);
}
glm::vec2 cross(glm::vec2 vec, float v) {
  return glm::vec2(v * vec.y, -v * vec.x);
}
float cross(glm::vec2 vec1, glm::vec2 vec2) {
  return vec1.x * vec2.y - vec1.y * vec2.x;
}

glm::vec2 normalize(glm::vec2 vec) {
  float length = glm::length(vec);
  if (length > kEpsilon) {
    float inv = 1.f / length;
    return {vec.x * inv, vec.y * inv};
  }

  return vec;
}

float squareLength(glm::vec2 vec) {
  return vec.x * vec.x + vec.y * vec.y;
}

float angleBetweenVecs(const glm::vec2 vec1, const glm::vec2 vec2) {
  float angle = 0.f;
  float a = glm::dot(vec1, vec2);

  if (vec2.x < 0) {
    angle = -std::acos(a);
  } else {
    angle = std::acos(a);
  }

  return angle;
}

} /* math */
} /* hx3d */
