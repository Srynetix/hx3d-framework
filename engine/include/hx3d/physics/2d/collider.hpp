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

#include <iostream>
#include <glm/vec2.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cfloat>

#include "hx3d/graphics/sprite.hpp"

namespace hx3d {
namespace physics2d {

struct Attractor;

struct Mass {
  Mass() {
    mass = 0;
    invMass = 0;

    inertia = 0;
    invInertia = 0;
  }

  void setMass(float amount) {
    mass = amount;
    invMass = (amount == 0) ? 0 : 1.f / amount;
  }

  void setInertia(float amount) {
    inertia = amount;
    invInertia = (amount == 0) ? 0 : 1.f / amount;
  }

  //////////////////

  float mass;
  float invMass;

  float inertia;
  float invInertia;
};

struct Material {
  Material() {
    staticFriction = 0.5f;
    dynamicFriction = 0.3f;
    restitution = 0.2f;
  }

  float staticFriction;
  float dynamicFriction;
  float restitution;
};

struct AttractorInformation {
  AttractorInformation() {
    current = nullptr;
  }

  Ptr<Attractor> current;
};

struct ColliderDefinition {
  ColliderDefinition(): unitCoef(1.f/30.f) {}

  float unitCoef;

  glm::vec2 position;
  Material material;
};

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

  void useDefinition(ColliderDefinition& def) {
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
  AttractorInformation attractors;
};

/////////////

} /* physics2d */
} /* hx3d */

#endif
