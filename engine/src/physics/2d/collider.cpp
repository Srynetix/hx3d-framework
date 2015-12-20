/*
    2D Collider.
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

#include "hx3d/physics/2d/collider.hpp"

#include "hx3d/math/vector_utils.hpp"

namespace hx3d {
namespace physics2d {

Collider::Definition::Definition():
  unitCoef(1.f/30.f) {}

Collider::Collider(Shape shapeType, const Type colliderType):
  position(0, 0),
  velocity(0, 0),
  force(0, 0),
  angularVelocity(0),
  torque(0),
  orientation(0),
  fixedRotation(false),
  type(colliderType),
  shape(shapeType)
  {}

Collider::~Collider() {}

void Collider::useDefinition(const Definition& def) {
  position = def.unitCoef * def.position;
}

void Collider::applyForce(const glm::vec2& amount) {
  force += amount;
}

void Collider::applyImpulse(const glm::vec2& amount, const glm::vec2& contact) {
  velocity += massData.invMass * amount;
  angularVelocity += massData.invInertia * math::cross(contact, amount);
}

void Collider::setDensity(float density) {
  if (type == Type::Static) {
    massData.setMass(0);
    massData.setInertia(0);
  } else {
    computeMass(density);
  }
}

} /* physics2d */
} /* hx3d */
