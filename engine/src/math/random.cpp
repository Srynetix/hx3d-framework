/*
    Random functions.
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

#include "hx3d/math/random.hpp"

#include <cstdlib>

namespace hx3d {
namespace math {

float randfloat() {
  return (float)rand() / (RAND_MAX + 1.f);
}

int random(int min, int max) {
  return rand() % (max-min + 1) + min;
}

bool flip_coin() {
  return random(0, 1) == 0;
}

} /* math */
} /* hx3d */
