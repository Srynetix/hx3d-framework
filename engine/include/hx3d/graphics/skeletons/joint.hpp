/*
    Skeleton joint.
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

#include "hx3d/graphics/skeletons/bone.hpp"
#include "hx3d/math/number_utils.hpp"

namespace hx3d {
namespace graphics {

class Joint {
public:
  Joint(Bone* boneA, Bone* boneB, glm::vec2 anchorA, glm::vec2 anchorB): boneA(boneA), boneB(boneB), anchorA(anchorA), anchorB(anchorB) {}

  void update() {
    auto vec = boneA->size * (anchorA - boneA->c_rotation_offset);
    auto s = sin(boneA->c_rotation);
    auto c = cos(boneA->c_rotation);
    auto nvec = glm::vec2(vec.x * c - vec.y * s, vec.x * s + vec.y * c);

    boneB->c_position = boneA->c_position + nvec;
    boneB->c_rotation_offset = anchorB;
    boneB->c_rotation = boneA->c_rotation + boneB->rotation;

    for (auto& joint: boneB->children) {
      joint->update();
    }
  }

  void rotate(float angle) {
    boneB->rotation = math::mclamp(boneB->rotation + angle, 0, 360);
    this->update();
  }

  void draw(const Pointer<Batch>& batch) {
    boneB->draw(batch);
  }

  Bone* boneA;
  Bone* boneB;
  glm::vec2 anchorA;
  glm::vec2 anchorB;
};

} /* graphics */
} /* hx3d */
