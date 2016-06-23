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
  Bone(float w, float h, float init_rotation): size(w, h), rotation(init_rotation) {
    parent = nullptr;
    sprite->setTexture(Core::Assets()->get<Texture>("box"));
    sprite->setTint(Color::Red);
    sprite->transform.size.x = size.x;
    sprite->transform.size.y = size.y;

    c_position = glm::vec2(0, 0);
    c_rotation_offset = glm::vec2(0, 0);
    c_rotation = rotation;
  }

  void draw(const Pointer<Batch>& batch) {
    Log.Info("O: %f / %f", c_position.x, c_position.y);
    auto bottomLeft = glm::vec2(c_position.x + size.x / 2, c_position.y + size.y / 2);
    bottomLeft -= size * c_rotation_offset;

    Log.Info("B: %f / %f", bottomLeft.x, bottomLeft.y);

    sprite->transform.position.x = bottomLeft.x;
    sprite->transform.position.y = bottomLeft.y;
    sprite->transform.rotation.z = c_rotation;

    batch->draw(sprite);
  }

  Joint* parent;
  std::vector<Joint*> children;

  glm::vec2 size;
  float rotation;

  glm::vec2 c_rotation_offset;
  glm::vec2 c_position;
  float c_rotation;

  Sprite::Ref sprite;
};

} /* graphics */
} /* hx3d */
