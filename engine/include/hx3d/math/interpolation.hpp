/*
    Interpolation functions.
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

#ifndef HX3D_MATH_INTERPOLATION
#define HX3D_MATH_INTERPOLATION

#include <glm/vec2.hpp>
#include <functional>

#include "hx3d/math/constants.hpp"
#include "hx3d/graphics/color.hpp"

namespace hx3d {
namespace math {

enum class Interpolation {
  Linear = 0,

  InQuad,
  OutQuad,
  InOutQuad,

  InCubic,
  OutCubic,
  InOutCubic,

  InQuart,
  OutQuart,
  InOutQuart,

  InQuint,
  OutQuint,
  InOutQuint,

  InSine,
  OutSine,
  InOutSine,

  InExpo,
  OutExpo,
  InOutExpo,

  InCirc,
  OutCirc,
  InOutCirc,

  InBack,
  OutBack,
  InOutBack,

  InBounce,
  OutBounce,
  InOutBounce,

  InElastic,
  OutElastic,
  InOutElastic
};

template <class T>
T interpolate(T a, T b, float t, Interpolation type);

template <>
inline Color interpolate(Color a, Color b, float t, Interpolation type);

} /* math */
} /* hx3d */

#include "hx3d/math/_inline/interpolation.inl.hpp"

#endif
