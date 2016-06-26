/*
    Skeleton bone.
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

#include <vector>
#include "hx3d/graphics/batches/batch.hpp"

namespace hx3d {
namespace graphics {

class Joint;
class Bone {
public:
  Bone(float w, float h, float rot, float depth = 0.f):
    size(w, h), rotation(rot), depth(depth) {

    sprite->setTexture(Core::Assets()->get<Texture>("box"));
    sprite->transform.size.x = size.x;
    sprite->transform.size.y = size.y;
    parent = nullptr;

    displacement = glm::vec2(0, 0);
    c_position = glm::vec2(0, 0);
    c_offset = glm::vec2(0.5f, 0.5f);
    c_rotation = rotation;
  }

  void draw(const Pointer<Batch>& batch) {
    auto off = size * (0.5f - c_offset);
    auto si = sin(glm::radians(c_rotation));
    auto co = cos(glm::radians(c_rotation));
    auto di = glm::vec2(off.x * co - off.y * si, off.x * si + off.y * co);

    auto pos = c_position + displacement + di;
    sprite->transform.position.x = pos.x;
    sprite->transform.position.y = pos.y;
    sprite->transform.rotation.z = glm::radians(c_rotation);

    batch->draw(sprite);
  }

  Pointer<Joint> parent;
  std::vector<Pointer<Joint>> children;

  glm::vec2 size;
  float rotation;
  glm::vec2 displacement;
  float depth;

  glm::vec2 c_offset;
  glm::vec2 c_position;
  float c_rotation;

  Sprite::Ref sprite;
};

} /* graphics */
} /* hx3d */
