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

#include "hx3d/graphics/utils/transform.hpp"

namespace hx3d {

Transform::Transform():
  position(0, 0, 0),
  scale(1, 1, 1),
  size(0, 0, 0),
  rotation(0, 0, 0) {}

glm::mat4 Transform::compute() {
  glm::mat4 model = glm::mat4(1.f);
  model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
  model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
  model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

  return model;
}

Transform Transform::add(const Transform& transform) {
  Transform t;
  t.position = position;
  t.rotation = rotation;
  t.scale = scale;
  t.size = size;

  t.position += transform.position;
  t.rotation += transform.rotation;
  return t;
}

} /* hx3d */
