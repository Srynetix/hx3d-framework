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

#include <glm/vec2.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cfloat>
#include <vector>

#include "hx3d/math/vector_utils.hpp"
#include "hx3d/utils/ptr.hpp"

#include "hx3d/physics/2d/mass.hpp"
#include "hx3d/physics/2d/material.hpp"

namespace hx3d {
namespace physics2d {

struct Attractor;
class Collider {
public:
  enum class Type {
    Static,
    Dynamic
  };

  enum class Shape {
    Circle,
    Polygon
  };

  struct Definition {
    Definition(): unitCoef(1.f/30.f) {}

    float unitCoef;

    glm::vec2 position;
    Material material;
  };

  Collider(Shape shapeType, const Type colliderType = Type::Dynamic) {
    position = {0, 0};
    velocity = {0, 0};
    force = {0, 0};
    angularVelocity = 0;

    torque = 0;
    orientation = 0;

    type = colliderType;
    shape = shapeType;
  }

  void useDefinition(const Definition& def) {
    position = def.unitCoef * def.position;
  }

  virtual ~Collider() {}

  virtual void computeMass(float density) = 0;
  virtual void setOrientation(float angle) = 0;

  void applyForce(const glm::vec2& amount) {
    force += amount;
  }

  void applyImpulse(const glm::vec2& amount, const glm::vec2& contact) {
    velocity += massData.invMass * amount;
    angularVelocity += massData.invInertia * math::cross(contact, amount);
  }

  void setDensity(float density) {
    if (type == Type::Static) {
      massData.setMass(0);
      massData.setInertia(0);
    } else {
      computeMass(density);
    }
  }

  ///////////////

  glm::vec2 position;
  glm::vec2 velocity;
  glm::vec2 gravityForce;
  glm::vec2 force;
  glm::vec2 gravityScale;

  float angularVelocity;
  float torque;
  float orientation;

  Type type;
  Shape shape;

  Material material;
  Mass massData;

  Ptr<Attractor> currentAttractor;
};

/////////////

} /* physics2d */
} /* hx3d */

#endif
