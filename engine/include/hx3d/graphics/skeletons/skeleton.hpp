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
#include "hx3d/utils/resource.hpp"
#include "hx3d/utils/yaml.hpp"

namespace hx3d {
namespace graphics {

class Skeleton: public Resource {
  HX3D_PTR(Skeleton)

public:
  Skeleton(float rootW, float rootH, float rootRotation) {
    bones["root"] = Make<Bone>(rootW, rootH, rootRotation);
    bones["root"]->c_offset = glm::vec2(0.5, 0.5);
  }

  Skeleton(std::string pathToConfig) {
    // Config file
    auto rootCfg = yaml::loadFromFile(pathToConfig);

    // Root
    auto rootNode = yaml::getNode(rootCfg, "root");
    float rootW = yaml::getValue<float>(rootNode, "w");
    float rootH = yaml::getValue<float>(rootNode, "h");
    float rootRot = yaml::getValue<float>(rootNode, "r", 0.f);
    bones["root"] = Make<Bone>(rootW, rootH, rootRot);

    // Bones
    auto rootBones = yaml::getNode(rootCfg, "bones");
    for (auto pair: rootBones) {
      auto& bone = pair.second;

      float boneW = yaml::getValue<float>(bone, "w");
      float boneH = yaml::getValue<float>(bone, "h");
      float boneRot = yaml::getValue<float>(bone, "r", 0.f);
      float boneDep = yaml::getValue<float>(bone, "d", 0.f);
      std::string boneName = pair.first.as<std::string>();

      this->addBone(boneName, boneW, boneH, boneRot, boneDep);
    }

    // Joints
    auto rootJoints = yaml::getNode(rootCfg, "joints");
    for (auto pair: rootJoints) {
      std::string jointName = pair.first.as<std::string>();
      auto& joint = pair.second;

      std::string a = yaml::getValue<std::string>(joint, "a");
      std::string b = yaml::getValue<std::string>(joint, "b");
      auto anchorA = yaml::getNode(joint, "anchorA");
      auto anchorB = yaml::getNode(joint, "anchorB");
      float anchorAx = yaml::getListValue<float>(anchorA, 0);
      float anchorAy = yaml::getListValue<float>(anchorA, 1);
      float anchorBx = yaml::getListValue<float>(anchorB, 0);
      float anchorBy = yaml::getListValue<float>(anchorB, 1);
      glm::vec2 limit = {0, 360};

      if (joint["limit"]) {
        limit.x = joint["limit"][0].as<float>();
        limit.y = joint["limit"][1].as<float>();
      }

      this->addJoint(jointName, a, b, glm::vec2(anchorAx, anchorAy), glm::vec2(anchorBx, anchorBy), limit);
    }
  }

  void setPosition(float x, float y) {
    bones["root"]->c_position.x = x;
    bones["root"]->c_position.y = y;

    for (auto& pair: joints) {
      pair.second->update();
    }
  }

  void addBone(std::string name, float w, float h, float rotation, float depth = 0) {
    bones[name] = Make<Bone>(w, h, rotation, depth);
  }

  void addJoint(std::string name, std::string a, std::string b, glm::vec2 anchorA, glm::vec2 anchorB, glm::vec2 limit = {0, 360}) {
    auto& boneA = bones[a];
    auto& boneB = bones[b];
    Pointer<Joint> joint = Make<Joint>(boneA, boneB, anchorA, anchorB, limit);

    boneA->children.push_back(joint);
    boneB->parent = joint;

    joints[name] = joint;
    joint->update();
  }

  void rotateRoot(float angle) {
    auto& root = bones["root"];
    root->rotation = math::mclamp(root->rotation + angle, 0, 360);
    root->c_rotation = root->rotation;

    for (auto& joint: root->children) {
      joint->update();
    }
  }

  void draw(const Pointer<Batch>& batch) {
    bones["root"]->draw(batch);

    for (auto& pair: joints) {
      pair.second->draw(batch);
    }
  }

  void rotateJoint(std::string name, float angle) {
    joints[name]->rotate(angle);
  }

  std::map<std::string, Pointer<Bone>> bones;
  std::map<std::string, Pointer<Joint>> joints;
};

} /* graphics */
} /* hx3d */
