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

#include "hx3d/graphics/skeletons/joint.hpp"
#include "hx3d/graphics/skeletons/bone.hpp"

#include "hx3d/math/number_utils.hpp"

#include <glm/glm.hpp>

namespace hx3d {
namespace graphics {

Joint::Joint(const Pointer<Bone>& a, const Pointer<Bone>& b, glm::vec2 anchorA, glm::vec2 anchorB, glm::vec2 limit, bool fixed): a(a), b(b), anchorA(anchorA), anchorB(anchorB), limit(limit), fixed(fixed) {}

void Joint::update() {
  auto posA = a->c_position + a->displacement;
  auto mvec = a->size * (anchorA - a->c_offset);
  auto si = sin(glm::radians(a->c_rotation));
  auto co = cos(glm::radians(a->c_rotation));
  auto nvec = glm::vec2(mvec.x * co - mvec.y * si, mvec.x * si + mvec.y * co);

  b->c_position = posA + nvec + b->displacement;
  b->c_offset = anchorB;

  if (fixed) {
    b->c_rotation = b->rotation;
  } else {
    b->c_rotation = a->c_rotation + b->rotation;
  }

  for (auto& joint: b->children) {
    joint->update();
  }
}

void Joint::rotate(float angle) {
  if (limit.x == 0 && limit.y == 360) {
    b->rotation = math::mclamp(b->rotation + angle, limit.x, limit.y);
  } else {
    b->rotation = math::clamp(b->rotation + angle, limit.x, limit.y);
  }

  this->update();
}

void Joint::draw(const Pointer<Batch>& batch) {
  b->draw(batch);
}

} /* graphics */
} /* hx3d */
