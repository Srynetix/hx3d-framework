/*
    2D circle collider.
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

#include "hx3d/physics/2d/collider.hpp"

namespace hx3d {
namespace physics2d {

/**
@brief Circle shaped collider
*/
class Circle: public Collider {
public:
  
  /**
  @brief Create a circle

  @param radius       Radius
  @param colliderType Collider type
  */
  Circle(float radius, const Type colliderType = Type::Dynamic);

  virtual void setOrientation(float angle) override;
  virtual void computeMass(float density) override;

  /// @brief Radius
  float radius;
};

} /* physics2d */
} /* hx3d */
