/*
    Number helper methods.
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

#ifndef HX3D_UTILS_NUMBERUTILS
#define HX3D_UTILS_NUMBERUTILS

namespace hx3d {
namespace math {

/**
@brief Simple clamp.

Block the value between min and max.

@param value  Value
@param min    Min
@param max    Max
@return New value
*/
float clamp(float value, float min, float max);

/**
@brief Modulo clamp.

Block the value between min and max.

If the value is > to max, it goes back to min.
If the value is < to min, it goes back to max.

@param value  Value
@param min    Min
@param max    Max
@return New value
*/
float mclamp(float value, float min, float max);

/**
@brief Modulo.
Handles negative values !

@param a First value
@param b Second value
@return Modulo of a and b
*/
int modulo(int a, int b);

/**
@brief Calculate the log2.

@param a Value
@return Log2
*/
float log2(int a);

} /* math */
} /* hx3d */

#endif
