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

#ifndef HX3D_PHYSICS_2D_COLLIDERS_CIRCLE
#define HX3D_PHYSICS_2D_COLLIDERS_CIRCLE

#include "hx3d/physics/2d/collider.hpp"

namespace hx3d {
namespace physics2d {
namespace colliders {

struct Circle: public Collider {
  float radius;

  Circle(float radius, const Type colliderType = Type::Dynamic):
    Collider(Shape::Circle, colliderType),
    radius(radius)
  {
    setDensity(1.f);
  }

  virtual void setOrientation(float angle) override {
   orientation = angle;
  }

  virtual void computeMass(float density) override {
    massData.setMass(density);
  }
};

} /* colliders */
} /* physics2d */
} /* hx3d */

#endif
