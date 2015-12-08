/*
    Base camera class.
    Inspired by LibGDX camera.

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

#include "hx3d/graphics/cameras/camera.hpp"

#include "hx3d/graphics/gl.hpp"
#include "hx3d/math/vector_utils.hpp"

namespace hx3d {

Camera::Camera(const float width, const float height, const float near, const float far):
  position(0.f),
  direction(0.f, 0.f, -1.f),
  up(0.f, 1.f, 0.f),
  near(near),
  far(far),
  viewportWidth(width),
  viewportHeight(height)
{}

void Camera::lookAt(glm::vec3 target) {
  target -= position;
  target = glm::normalize(target);

  if (target != glm::vec3(0)) {
    float dot = glm::dot(target, up);
    if (std::abs(dot - 1) < 0.00001f) {
      up = direction;
      up *= -1;
    } else if (std::abs(dot + 1) < 0.00001f) {
      up = direction;
    }

    direction = target;

    // normalize up
    glm::vec3 tmp(direction);
    tmp = glm::cross(tmp, up);
    tmp = glm::normalize(tmp);

    up = tmp;
    up = glm::cross(up, direction);
    up = glm::normalize(up);
  }
}

void Camera::translate(const glm::vec3 vec) {
  position += vec;
}

void Camera::rotate(const float angle, const glm::vec3 axis) {
  direction = math::rotate(direction, glm::radians(angle), axis);
  up = math::rotate(up, angle, axis);
}

void Camera::rotateAround(const glm::vec3 center, const float angle, const glm::vec3 axis) {
  glm::vec3 tmp(center);
  tmp -= position;
  translate(tmp);
  rotate(angle, axis);

  tmp = math::rotate(tmp, glm::radians(angle), axis);
  translate(-tmp);
}

////////////////////

} /* hx3d */
