/*
    Skeleton.
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

#include "hx3d/graphics/skeletons/joint.hpp"

namespace hx3d {
namespace graphics {

class Skeleton {
  HX3D_PTR(Skeleton)

public:
  Skeleton(float rootW, float rootH, float rootRotation) {
    bones["ROOT"] = new Bone(rootW, rootH, rootRotation);
    bones["ROOT"]->c_rotation_offset = glm::vec2(0.5, 0.5);
  }

  void setPosition(float x, float y) {
    bones["ROOT"]->c_position.x = x;
    bones["ROOT"]->c_position.y = y;

    for (auto& pair: joints) {
      pair.second->update();
    }
  }

  void addBone(std::string name, float w, float h, float rotation) {
    bones[name] = new Bone(w, h, rotation);
  }

  void addJoint(std::string name, std::string a, std::string b, glm::vec2 anchorA, glm::vec2 anchorB) {
    auto& boneA = bones[a];
    auto& boneB = bones[b];
    auto joint = new Joint(boneA, boneB, anchorA, anchorB);

    boneA->children.push_back(joint);
    boneB->parent = joint;

    joints[name] = joint;
    joint->update();
  }

  void rotateRoot(float angle) {
    auto& root = bones["ROOT"];
    root->rotation = math::mclamp(root->rotation + angle, 0, 360);
    root->c_rotation = root->rotation;

    for (auto& joint: root->children) {
      joint->update();
    }
  }

  void draw(const Pointer<Batch>& batch) {
    bones["ROOT"]->draw(batch);

    for (auto& pair: joints) {
      pair.second->draw(batch);
    }
  }

  void rotateJoint(std::string name, float angle) {
    joints[name]->rotate(angle);
  }

  std::map<std::string, Bone*> bones;
  std::map<std::string, Joint*> joints;
};

} /* graphics */
} /* hx3d */
