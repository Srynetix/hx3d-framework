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

#include "hx3d/graphics/skeletons/skeleton.hpp"

#include "hx3d/graphics/skeletons/joint.hpp"
#include "hx3d/graphics/skeletons/bone.hpp"
#include "hx3d/math/number_utils.hpp"
#include "hx3d/utils/yaml.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace graphics {

Skeleton::Skeleton(float rootW, float rootH, float rootRotation) {
  bones["root"] = Make<Bone>(rootW, rootH, rootRotation);
  bones["root"]->c_offset = glm::vec2(0.5, 0.5);
}

Skeleton::Skeleton(std::string pathToConfig) {
  // Config file
  auto document = yaml::Document::loadFromFile(pathToConfig);

  // Root
  float rootW = document.fetch<float>("root", "w");
  float rootH = document.fetch<float>("root", "h");
  float rootRot = document.fetch<float>("root", "r");

  bones["root"] = Make<Bone>(rootW, rootH, rootRot);

  // Bones
  auto rootBones = document.fetchNode("bones");
  for (auto pair: document.listPairs(rootBones)) {
    auto bone = pair.second;

    float boneW = document.fetch<float>(bone, "w");
    float boneH = document.fetch<float>(bone, "h");
    float boneRot = 0.f;
    float boneDep = 0.f;
    std::string boneName = pair.first;

    this->addBone(boneName, boneW, boneH, boneRot, boneDep);
  }

  // Joints
  auto rootJoints = document.fetchNode("joints");
  for (auto pair: document.listPairs(rootJoints)) {
    std::string jointName = pair.first;
    auto joint = pair.second;

    std::string a = document.fetch<std::string>(joint, "a");
    std::string b = document.fetch<std::string>(joint, "b");
    auto anchorA = document.fetchNode(joint, "anchorA");
    auto anchorB = document.fetchNode(joint, "anchorB");
    float anchorAx = document.fetchIndex<float>(anchorA, 0);
    float anchorAy = document.fetchIndex<float>(anchorA, 1);
    float anchorBx = document.fetchIndex<float>(anchorB, 0);
    float anchorBy = document.fetchIndex<float>(anchorB, 1);

    glm::vec2 limit = {0, 360};

    // if (joint["limit"]) {
      // limit.x = joint["limit"][0].as<float>();
      // limit.y = joint["limit"][1].as<float>();
    // }

    this->addJoint(jointName, a, b, glm::vec2(anchorAx, anchorAy), glm::vec2(anchorBx, anchorBy), limit);
  }
}

void Skeleton::setPosition(float x, float y) {
  bones["root"]->c_position.x = x;
  bones["root"]->c_position.y = y;

  for (auto& pair: joints) {
    pair.second->update();
  }
}

void Skeleton::addBone(std::string name, float w, float h, float rotation, float depth) {
  bones[name] = Make<Bone>(w, h, rotation, depth);
}

void Skeleton::addJoint(std::string name, std::string a, std::string b, glm::vec2 anchorA, glm::vec2 anchorB, glm::vec2 limit) {
  auto& boneA = bones[a];
  auto& boneB = bones[b];
  Pointer<Joint> joint = Make<Joint>(boneA, boneB, anchorA, anchorB, limit);

  boneA->children.push_back(joint);
  boneB->parent = joint;

  joints[name] = joint;
  joint->update();
}

void Skeleton::rotateRoot(float angle) {
  auto& root = bones["root"];
  root->rotation = math::mclamp(root->rotation + angle, 0, 360);
  root->c_rotation = root->rotation;

  for (auto& joint: root->children) {
    joint->update();
  }
}

void Skeleton::draw(const Pointer<Batch>& batch) {
  bones["root"]->draw(batch);

  for (auto& pair: joints) {
    pair.second->draw(batch);
  }
}

void Skeleton::rotateJoint(std::string name, float angle) {
  joints[name]->rotate(angle);
}

} /* graphics */
} /* hx3d */
