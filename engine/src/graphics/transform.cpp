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

#include "hx3d/math/number_utils.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace graphics {

Transform::Transform():
  _dirty(true),
  _lastCompute(1.f),
  _position(0.f),
  _size(1.f),
  _scale(1.f),
  _r(0.f),
  _anchor(0.5f)
  {}

glm::mat4 Transform::compute() {
  if (_dirty) {
    _lastCompute = glm::mat4(1.f);

    // Anchor offset
    glm::vec3 normAnchor = _anchor - glm::vec3(0.5);
    glm::vec3 disp = normAnchor * _size * _scale;

    _lastCompute = glm::translate(_lastCompute, _position + disp);
    _lastCompute = glm::rotate(_lastCompute, _r.x, glm::vec3(1, 0, 0));
    _lastCompute = glm::rotate(_lastCompute, _r.y, glm::vec3(0, 1, 0));
    _lastCompute = glm::rotate(_lastCompute, _r.z, glm::vec3(0, 0, 1));
    _lastCompute = glm::translate(_lastCompute, -disp);
    _lastCompute = glm::scale(_lastCompute, _size);
    _lastCompute = glm::scale(_lastCompute, _scale);

    _dirty = false;
  }

  return _lastCompute;
}

Transform Transform::add(const Transform& transform) {
  Transform result;
  result._position = _position;
  result._r = _r;
  result._scale = _scale;
  result._size = _size;

  result._r += transform._r;

  float s = std::sin(transform._r.z);
  float c = std::cos(transform._r.z);
  float nx = c * _position.x - s * _position.y + transform._position.x;
  float ny = s * _position.x + c * _position.y + transform._position.y;

  result._position.x = nx;
  result._position.y = ny;

  result._dirty = true;

  return result;
}

bool Transform::contains(const glm::vec2& point) {
  float width = _scale.x * _size.x;
  float height = _scale.y * _size.y;

  float minX = _position.x - width / 2;
  float maxX = _position.x + width / 2;
  float minY = _position.y - height / 2;
  float maxY = _position.y + height / 2;

  return ((minX <= point.x && maxX >= point.x) &&
          (minY <= point.y && maxY >= point.y));
}

//////////

void Transform::setAnchor(float x, float y) {
  setAnchor(x, y, _anchor.z);
}

void Transform::setAnchor(float x, float y, float z) {
  if (_anchor.x == x && _anchor.y == y && _anchor.z == z) return;

  _anchor.x = x;
  _anchor.y = y;
  _anchor.z = z;

  _dirty = true;
}

void Transform::setAnchorX(float x) {
  setAnchor(x, _anchor.y, _anchor.z);
}

void Transform::setAnchorY(float y) {
  setAnchor(_anchor.x, y, _anchor.z);
}

void Transform::setAnchorZ(float z) {
  setAnchor(_anchor.x, _anchor.y, z);
}

void Transform::setAnchorCenter() {
  setAnchor(0.5f, 0.5f, 0.5f);
}

void Transform::setAnchorBottomLeft() {
  setAnchor(0, 0, 0.5);
}

void Transform::setAnchorBottomCenter() {
  setAnchor(0.5, 0, 0.5);
}

void Transform::setX(float x) {
  if (x == _position.x) return;

  _position.x = x;
  _dirty = true;
}

void Transform::setY(float y) {
  if (y == _position.y) return;

  _position.y = y;
  _dirty = true;
}

void Transform::setZ(float z) {
  if (z == _position.z) return;

  _position.z = z;
  _dirty = true;
}

void Transform::setRotationX(float x) {
  if (x == _r.x) return;

  _r.x = x;
  _dirty = true;
}

void Transform::setRotationY(float y) {
  if (y == _r.y) return;

  _r.y = y;
  _dirty = true;
}

void Transform::setScaleX(float x) {
  if (x == _scale.x) return;

  _scale.x = x;
  _dirty = true;
}

void Transform::setScaleY(float y) {
  if (y == _scale.y) return;

  _scale.y = y;
  _dirty = true;
}

void Transform::setScaleZ(float z) {
  if (z == _scale.z) return;

  _scale.z = z;
  _dirty = true;
}

void Transform::setWidth(float w) {
  if (w == _size.x) return;

  _size.x = w;
  _dirty = true;
}

void Transform::setHeight(float h) {
  if (h == _size.y) return;

  _size.y = h;
  _dirty = true;
}

void Transform::setDepth(float d) {
  if (d == _size.z) return;

  _size.z = d;
  _dirty = true;
}

void Transform::setPosition(float x, float y) {
  setPosition(x, y, _position.z);
}

void Transform::setPosition(float x, float y, float z) {
  if (x == _position.x && y == _position.y && z == _position.z) return;

  _position = {x, y, z};
  _dirty = true;
}

void Transform::setPosition(const glm::vec2& v) {
  setPosition(v.x, v.y);
}

void Transform::setPosition(const glm::vec3& v) {
  setPosition(v.x, v.y, v.z);
}

void Transform::setRotation(float r) {
  setRotation(_r.x, _r.y, r);
}

void Transform::setRotation(float x, float y, float z) {
  if (x == _r.x && y == _r.y && z == _r.z) return;

  _r = {x, y, z};
  _dirty = true;
}

void Transform::setRotation(const glm::vec3& v) {
  setRotation(v.x, v.y, v.z);
}

void Transform::setScale(float s) {
  setScale(s, s);
}

void Transform::setScale(float sx, float sy) {
  setScale(sx, sy, _scale.z);
}

void Transform::setScale(float sx, float sy, float sz) {
  if (sx == _scale.x && sy == _scale.y && sz == _scale.z) return;

  _scale = {sx, sy, sz};
  _dirty = true;
}

void Transform::setScale(const glm::vec3& v) {
  setScale(v.x, v.y, v.z);
}

void Transform::setSize(float w, float h) {
  setSize(w, h, _size.z);
}

void Transform::setSize(float w, float h, float d) {
  if (w == _size.x && h == _size.y && d == _size.z) return;

  _size = {w, h, d};
  _dirty = true;
}

void Transform::setSize(const glm::vec2& v) {
  setSize(v.x, v.y);
}

void Transform::setSize(const glm::vec3& v) {
  setSize(v.x, v.y, v.z);
}

/////////////

void Transform::resize(float w, float h) {
  resize(w, h, 0);
}

void Transform::resize(float w, float h, float d) {
  if (w == 0 && h == 0 && d == 0) return;
  setSize(_size.x + w, _size.y + h, _size.z + d);
}

void Transform::move(float x, float y) {
  move(x, y, 0);
}

void Transform::move(float x, float y, float z) {
  if (x == 0 && y == 0 && z == 0) return;
  setPosition(_position.x + x, _position.y + y, _position.z + z);
}

void Transform::scale(float sx, float sy) {
  scale(sx, sy, 0);
}

void Transform::scale(float sx, float sy, float sz) {
  if (sx == 0 && sy == 0 && sz == 0) return;
  setScale(_scale.x + sx, _scale.y + sy, _scale.z + sz);
}

void Transform::rotate(float r) {
  rotate(0, 0, r);
}

void Transform::rotate(float x, float y, float z) {
  if (x == 0 && y == 0 && z == 0) return;
  setRotation(_r.x + x, _r.y + y, _r.z + z);
}

/////////

float Transform::getX() const {
  return _position.x;
}

float Transform::getY() const {
  return _position.y;
}

float Transform::getZ() const {
  return _position.z;
}

float Transform::getRotationX() const {
  return _r.x;
}

float Transform::getRotationY() const {
  return _r.y;
}

float Transform::getScaleX() const {
  return _scale.x;
}

float Transform::getScaleY() const {
  return _scale.y;
}

float Transform::getScaleZ() const {
  return _scale.z;
}

float Transform::getWidth() const {
  return _size.x;
}

float Transform::getHeight() const {
  return _size.y;
}

float Transform::getDepth() const {
  return _size.z;
}

float Transform::getTotalWidth() const {
  return getWidth() * getScaleX();
}

float Transform::getTotalHeight() const {
  return getHeight() * getScaleY();
}

float Transform::getTotalDepth() const {
  return getDepth() * getScaleZ();
}

glm::vec2 Transform::getPosition() const {
  return {_position.x, _position.y};
}

glm::vec3 Transform::get3DPosition() const {
  return _position;
}

glm::vec2 Transform::getSize() const {
  return {_size.x, _size.y};
}

glm::vec3 Transform::get3DSize() const {
  return _size;
}

glm::vec2 Transform::getScale() const {
  return {_scale.x, _scale.y};
}

glm::vec3 Transform::get3DScale() const {
  return _scale;
}

glm::vec2 Transform::getTotalSize() const {
  return getSize() * getScale();
}

glm::vec3 Transform::getTotal3DSize() const {
  return _size * _scale;
}

float Transform::getRotation() const {
  return _r.z;
}

float& Transform::getRotation() {
  return _r.z;
}

glm::vec3 Transform::get3DRotation() const {
  return _r;
}

bool Transform::isDirty() const {
  return _dirty;
}

void Transform::setTransform(const Transform &transform) {
  _position = transform._position;
  _scale = transform._scale;
  _size = transform._size;
  _r = transform._r;
  _lastCompute = transform._lastCompute;
  _anchor = transform._anchor;
  _dirty = transform._dirty;
}

} /* graphics */
} /* hx3d */
