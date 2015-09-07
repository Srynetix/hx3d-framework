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

#include "hx3d/math/number_utils.hpp"

#include <cmath>

namespace hx3d {
namespace math {

float clamp(float value, float min, float max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

float mclamp(float value, float min, float max) {
  if (value < min) return max - modulo(value, min);
  if (value >= max) return min + modulo(value, max);
  return value;
}

int modulo(int a, int b) {
  if (a < 0 && b < 0) {
    return -(a%b);
  }

  return a >= 0 ? a % b : (b - static_cast<unsigned int>(std::abs(a%b))) % b;
}

} /* math */
} /* hx3d */
