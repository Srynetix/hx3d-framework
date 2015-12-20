/*
    Vector helper methods.
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

#ifndef HX3D_MATH_VECTORUTILS
#define HX3D_MATH_VECTORUTILS

#include <glm/glm.hpp>
#include <Box2D/Common/b2Math.h>

namespace hx3d {
namespace math {

const float kEpsilon = 0.0001;

/**
Rotate a vector of an angle on one/multiple axis.

@param vector Vector
@param angle  Angle
@param axis   Direction(s)
*/
glm::vec3 rotate(glm::vec3 vector, float angle, glm::vec3 axis);

glm::vec2 cross(glm::vec2 vec, float v);
glm::vec2 cross(float v, glm::vec2 vec);
float cross(glm::vec2 vec1, glm::vec2 vec2);

glm::vec2 normalize(glm::vec2 vec);
float squareLength(glm::vec2 vec);

float angleBetweenVecs(const glm::vec2 vec1, const glm::vec2 vec2);

template <class T>
inline bool epsEqual(T v1, T v2) {
  return std::abs(v1 - v2) <= kEpsilon;
}

} /* math */
} /* hx3d */

#endif
