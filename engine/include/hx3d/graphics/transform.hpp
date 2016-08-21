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

  glm::mat4 compute();
  Transform add(const Transform& transform);
  bool contains(const glm::vec2& point);

  ///////////

  void setAnchor(float x, float y);
  void setAnchor(float x, float y, float z);
  void setAnchorX(float x);
  void setAnchorY(float y);
  void setAnchorZ(float z);

  void setAnchorCenter();
  void setAnchorBottomLeft();
  void setAnchorBottomCenter();

  void setX(float x);
  void setY(float y);
  void setZ(float z);

  void setRotationX(float x);
  void setRotationY(float y);

  void setScaleX(float x);
  void setScaleY(float y);
  void setScaleZ(float z);

  void setWidth(float w);
  void setHeight(float h);
  void setDepth(float d);

  void setPosition(float x, float y);
  void setPosition(float x, float y, float z);
  void setPosition(const glm::vec2& v);
  void setPosition(const glm::vec3& v);

  void setRotation(float r);
  void setRotation(float x, float y, float z);
  void setRotation(const glm::vec3& v);

  void setScale(float s);
  void setScale(float sx, float sy);
  void setScale(float sx, float sy, float sz);
  void setScale(const glm::vec3& v);

  void setSize(float w, float h);
  void setSize(float w, float h, float d);
  void setSize(const glm::vec2& v);
  void setSize(const glm::vec3& v);

  /////////////

  void resize(float w, float h);
  void resize(float w, float h, float d);

  void move(float x, float y);
  void move(float x, float y, float z);

  void scale(float sx, float sy);
  void scale(float sx, float sy, float sz);

  void rotate(float r);
  void rotate(float x, float y, float z);

  /////////

  float getX() const;
  float getY() const;
  float getZ() const;

  float getRotationX() const;
  float getRotationY() const;

  float getScaleX() const;
  float getScaleY() const;
  float getScaleZ() const;

  float getWidth() const;
  float getHeight() const;
  float getDepth() const;

  float getTotalWidth() const;
  float getTotalHeight() const;
  float getTotalDepth() const;

  glm::vec2 getPosition() const;
  glm::vec2 getSize() const;
  glm::vec2 getScale() const;
  glm::vec2 getTotalSize() const;
  float getRotation() const;
  float& getRotation();

  glm::vec3 get3DPosition() const;
  glm::vec3 get3DSize() const;
  glm::vec3 get3DScale() const;
  glm::vec3 getTotal3DSize() const;
  glm::vec3 get3DRotation() const;

  bool isDirty() const;

private:
  bool _dirty;

  glm::mat4 _lastCompute;

  glm::vec3 _position;
  glm::vec3 _size;
  glm::vec3 _scale;
  glm::vec3 _r;
  glm::vec3 _anchor;
};

} /* graphics */
} /* hx3d */
