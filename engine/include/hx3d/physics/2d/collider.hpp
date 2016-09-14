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

#pragma once

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/object_map.hpp"

#include "hx3d/physics/2d/mass.hpp"
#include "hx3d/physics/2d/material.hpp"

#include <glm/vec2.hpp>

namespace hx3d {
namespace physics2d {

class Attractor;

/**
@brief Physical collider
*/
class Collider {
public:
  HX3D_PTR(Collider)

  /**
  @brief Collider type
  */
  enum class Type {
    /// @brief Static: no forces or velocity
    Static,
    /// @brief Dynamic: forces and velocity
    Dynamic,
    /// @brief Kinematic: no forces but velocity
    Kinematic
  };

  /**
  @brief Collider shape
  */
  enum class Shape {
    /// @brief Circle shape
    Circle,
    /// @brief Polygon shape
    Polygon
  };

  /**
  @brief Collider definition
  */
  struct Definition {
    Definition();

    /// @brief Physical ratio
    float unitCoef;

    /// @brief Position
    glm::vec2 position;

    /// @brief Material
    Material material;

    /// @brief Mask
    unsigned int mask;
    /// @brief Category
    unsigned int category;
  };

  /**
  @brief Create a collider

  @param shapeType    Collider shape
  @param colliderType Collider type
  */
  Collider(const Shape shapeType, const Type colliderType = Type::Dynamic);
  virtual ~Collider();

  /**
  @brief Apply a definition on the collider

  @param def Collider definition
  */
  void useDefinition(const Definition& def);

  /**
  @brief Compute the collider mass

  @param density Density
  */
  virtual void computeMass(float density) = 0;

  /**
  @brief Set the collider orientation

  @param angle Angle in radians
  */
  virtual void setOrientation(float angle) = 0;

  /**
  @brief Apply a force

  @param amount Amount
  */
  void applyForce(const glm::vec2& amount);

  /**
  @brief Apply an impulse

  @param amount   Amount
  @param contact  Contact point
  */
  void applyImpulse(const glm::vec2& amount, const glm::vec2& contact);

  /**
  @brief Set collider density

  @param density Density
  */
  void setDensity(float density);

  ///////////////

  /// @brief Position
  glm::vec2 position;
  /// @brief Velocity
  glm::vec2 velocity;
  /// @brief Force
  glm::vec2 force;

  /// @brief Gravity force
  glm::vec2 gravityForce;
  /// @brief Gravity scale
  glm::vec2 gravityScale;
  /// @brief Air friction scale
  float airFrictionScale;

  /// @brief Angular velocity
  float angularVelocity;
  /// @brief Torque
  float torque;
  /// @brief Orientation
  float orientation;

  /// @brief Fixed rotation ?
  bool fixedRotation;

  /// @brief Mask
  unsigned int mask;
  /// @brief Category
  unsigned int category;

  /// @brief Type
  Type type;
  /// @brief Shape
  Shape shape;

  /// @brief Material
  Material material;
  /// @brief Mass data
  Mass massData;

  /// @brief Current attractor
  Pointer<Attractor> currentAttractor;
  /// @brief User data
  ObjectMap userData;
};

} /* physics2d */
} /* hx3d */
