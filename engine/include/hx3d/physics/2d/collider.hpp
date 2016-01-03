/*
    2D collider.
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

#ifndef HX3D_PHYSICS_2D_COLLIDER
#define HX3D_PHYSICS_2D_COLLIDER

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/object_map.hpp"

#include "hx3d/physics/2d/mass.hpp"
#include "hx3d/physics/2d/material.hpp"

#include <glm/glm.hpp>

namespace hx3d {
namespace physics2d {

struct Attractor;
class Collider {
public:
  enum class Type {
    Static,
    Dynamic,
    Kinematic
  };

  enum class Shape {
    Circle,
    Polygon
  };

  struct Definition {
    Definition();

    float unitCoef;

    glm::vec2 position;
    Material material;

    unsigned int mask;
    unsigned int category;
  };

  Collider(Shape shapeType, const Type colliderType = Type::Dynamic);

  void useDefinition(const Definition& def);

  virtual ~Collider();

  virtual void computeMass(float density) = 0;
  virtual void setOrientation(float angle) = 0;

  void applyForce(const glm::vec2& amount);
  void applyImpulse(const glm::vec2& amount, const glm::vec2& contact);
  void setDensity(float density);

  ///////////////

  glm::vec2 position;
  glm::vec2 velocity;
  glm::vec2 gravityForce;
  glm::vec2 force;
  glm::vec2 gravityScale;

  float angularVelocity;
  float torque;
  float orientation;

  bool fixedRotation;

  unsigned int mask;
  unsigned int category;

  Type type;
  Shape shape;

  Material material;
  Mass massData;

  Ptr<Attractor> currentAttractor;
  ObjectMap userData;
};

/////////////

} /* physics2d */
} /* hx3d */

#endif
