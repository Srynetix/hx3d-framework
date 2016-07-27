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

#include "hx3d/graphics/transform.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace graphics {

Transform::Transform():
  position(0, 0, 0),
  scale(1, 1, 1),
  size(1, 1, 1),
  rotation(0, 0, 0) {}

Transform& Transform::operator=(const Transform& transform) {
  position = transform.position;
  scale = transform.scale;
  size = transform.size;
  rotation = transform.rotation;

  return *this;
}

glm::mat4 Transform::compute() {
  glm::mat4 model = glm::mat4(1.f);
  model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
  model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
  model = glm::scale(model, glm::vec3(size.x, size.y, size.z));
  model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

  return model;
}

Transform Transform::add(const Transform& transform) {
  Transform t;
  t.position = position;
  t.rotation = rotation;
  t.scale = scale;
  t.size = size;

  t.rotation += transform.rotation;

  float s = std::sin(transform.rotation.z);
  float c = std::cos(transform.rotation.z);

  float nx = c * position.x - s * position.y + transform.position.x;
  float ny = s * position.x + c * position.y + transform.position.y;

  t.position.x = nx;
  t.position.y = ny;

  return t;
}

glm::vec3 Transform::realSize() {
  return size * scale;
}

bool Transform::contains(glm::vec2 point) {
  float width = scale.x * size.x;
  float height = scale.y * size.y;

  float minX = position.x - width / 2;
  float maxX = position.x + width / 2;
  float minY = position.y - height / 2;
  float maxY = position.y + height / 2;

  return ((minX <= point.x && maxX >= point.x) &&
    (minY <= point.y && maxY >= point.y));
}

void Transform::show() {
  auto Log = Logger::getLogger("graphics");
  
  Log.Info("-- Transform");
  Log.Info("\t Pos: [%f, %f, %f]", position.x, position.y, position.z);
  Log.Info("\t Sca: [%f, %f, %f]", scale.x, scale.y, scale.z);
  Log.Info("\t Siz: [%f, %f, %f]", size.x, size.y, size.z);
  Log.Info("\t Rot: [%f, %f, %f]", rotation.x, rotation.y, rotation.z);
  Log.Info("-- END Transform");
}

} /* graphics */
} /* hx3d */
