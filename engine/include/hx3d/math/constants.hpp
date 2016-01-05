/*
    Math constants.
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

#ifndef HX3D_MATH_CONSTANTS
#define HX3D_MATH_CONSTANTS

#include <complex>

typedef std::complex<double> Complex;

namespace hx3d {

/**
@brief Math structures and functions
*/
namespace math {

/// @brief Float epsilon
const float kEpsilon = 0.0001;
/// @brief PI
const double PI = 3.141592653589793238460;

} /* math */
} /* hx3d */

#endif
