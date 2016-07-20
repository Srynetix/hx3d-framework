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

#include "hx3d/utils/resource.hpp"
#include "hx3d/utils/reference.hpp"

#include <map>
#include <glm/vec2.hpp>

namespace hx3d {
namespace graphics {

class Bone;
class Joint;
class Batch;

class Skeleton: public Resource {
  HX3D_PTR(Skeleton)

public:
  Skeleton(std::string pathToConfig);
  Skeleton(float rootW, float rootH, float rootRotation);

  void setPosition(float x, float y);

  void addBone(std::string name, float w, float h, float rotation, float depth = 0);
  void addJoint(std::string name, std::string a, std::string b, glm::vec2 anchorA, glm::vec2 anchorB, glm::vec2 limit = {0, 360});

  void rotateRoot(float angle);
  void rotateJoint(std::string name, float angle);

  void draw(const Pointer<Batch>& batch);

private:
  std::map<std::string, Pointer<Bone>> bones;
  std::map<std::string, Pointer<Joint>> joints;
};

} /* graphics */
} /* hx3d */
