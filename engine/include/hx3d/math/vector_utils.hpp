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

#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace hx3d {
namespace math {

/**
@brief Rotate a vector of an angle on one/multiple axis.

@param vector Vector
@param angle  Angle
@param axis   Direction(s)

@return Rotated vector
*/
glm::vec3 rotate(glm::vec3 vector, float angle, glm::vec3 axis);

/**
@brief Calculate the cross product vector between a 2D vector and a scalar.

@param vec  2D vector
@param v    Scalar

@return Cross product vector
*/
glm::vec2 cross(glm::vec2 vec, float v);

/**
@brief Calculate the cross product vector between a scalar and a 2D vector.

@param v    Scalar
@param vec  2D vector

@return Cross product vector
*/
glm::vec2 cross(float v, glm::vec2 vec);

/**
@brief Calculate the cross product between two 2D vectors.

@param vec1 First vector
@param vec2 Second vector

@return Cross product value
*/
float cross(glm::vec2 vec1, glm::vec2 vec2);

/**
@brief Normalize a 2D vector.

@param vec Vector

@return Normalized vector
*/
glm::vec2 normalize(glm::vec2 vec);

/**
@brief Compute the square length of a 2D vector.

@param vec Vector

@return Square length
*/
float squareLength(glm::vec2 vec);

/**
@brief Compute the angle between two 2D vectors

@param vec1 First vector
@param vec2 Second vector

@return Angle
*/
float angleBetweenVecs(const glm::vec2 vec1, const glm::vec2 vec2);

/**
@brief Test values equality with epsilon

@param v1 First value
@param v2 Second value

@return True/False
*/
template <class T>
inline bool epsEqual(T v1, T v2);

} /* math */
} /* hx3d */

#include "hx3d/math/_inline/vector_utils.inl.hpp"
