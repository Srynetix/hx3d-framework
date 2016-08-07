/*
    Random utils.
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

namespace hx3d {
namespace math {

template <class T>
T random(T min, T max) {
  return rand() % (max - min + 1) + min;
}

template <>
inline float random(float min, float max) {
  return rand() % (int)(max - min + 1) + (int)min;
}

template <class T>
T random(std::vector<T>& vector) {
  int p = random(0, vector.size() - 1);
  return vector.at(p);
}

} /* math */
} /* hx3d */
