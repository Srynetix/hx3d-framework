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

/**
Rotate a vector of an angle on one/multiple axis.

@param vector Vector
@param angle  Angle
@param axis   Direction(s)
*/
glm::vec3 rotate(glm::vec3 vector, float angle, glm::vec3 axis);

/**
Convert a Box2D vector to GLM vector.

@param vector Box2D vector
@return GLM vector
*/
glm::vec2 convert(b2Vec2 vector);

/**
Convert a GLM vector to Box2D vector.

@param vector GLM vector
@return Box2D vector
*/
b2Vec2 convert(glm::vec2 vector);

} /* math */
} /* hx3d */

#endif
