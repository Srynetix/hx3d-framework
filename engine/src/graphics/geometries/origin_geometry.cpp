/*
    Origin models.
    Used at point (0, 0, 0) to show the origin.

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

#include "hx3d/graphics/geometries/origin_geometry.hpp"

namespace hx3d {
namespace graphics {

OriginGeometry::OriginGeometry(): Geometry() {

  setAttribute("Position", std::vector<float> {

    // Y pyramid (0 - 4)
    -0.125f, 0.75f, -0.125f,
    0.125f, 0.75f, -0.125f,
    0.125f, 0.75f, 0.125f,
    -0.125f, 0.75f, 0.125f,
    0, 1, 0,

    // Y base (5 - 12)
    -0.0625f, 0.0625f, -0.0625f,
    0.0625f, 0.0625f, -0.0625f,
    0.0625f, 0.0625f, 0.0625f,
    -0.0625f, 0.0625f, 0.0625f,
    -0.0625f, 0.75f, -0.0625f,
    0.0625f, 0.75f, -0.0625f,
    0.0625f, 0.75f, 0.0625f,
    -0.0625f, 0.75f, 0.0625f,

    // X pyramid (13 - 17)
    0.75f, -0.125f, -0.125f,
    0.75f, -0.125f, 0.125f,
    0.75f, 0.125f, 0.125f,
    0.75f, 0.125f, -0.125f,
    1, 0, 0,

    // X base (18 - 25)
    0.0625f, -0.0625f, -0.0625f,
    0.0625f, -0.0625f, 0.0625f,
    0.0625f, 0.0625f, 0.0625f,
    0.0625f, 0.0625f, -0.0625f,
    0.75f, -0.0625f, -0.0625f,
    0.75f, -0.0625f, 0.0625f,
    0.75f, 0.0625f, 0.0625f,
    0.75f, 0.0625f, -0.0625f,

    // Z pyramid (26 - 30)
    -0.125f, -0.125f, -0.75f,
    0.125f, -0.125f, -0.75f,
    0.125f, 0.125f, -0.75f,
    -0.125f, 0.125f, -0.75f,
    0, 0, -1,

    // Z base (31 - 38)
    -0.0625f, -0.0625f, -0.0625f,
    0.0625f, -0.0625f, -0.0625f,
    0.0625f, 0.0625f, -0.0625f,
    -0.0625f, 0.0625f, -0.0625f,
    -0.0625f, -0.0625f, -0.75f,
    0.0625f, -0.0625f, -0.75f,
    0.0625f, 0.0625f, -0.75f,
    -0.0625f, 0.0625f, -0.75f,

    // Last point (39)
    -0.0625f, -0.0625f, 0.0625f
  });

  setIndices(std::vector<GLushort> {

    // Y pyramid
    0, 1, 2,
    0, 2, 3,
    0, 4, 1,
    1, 4, 2,
    2, 4, 3,
    3, 4, 0,

    // Y base
    5, 6, 7,
    5, 7, 8,
    5, 6, 10,
    5, 10, 9,
    6, 7, 11,
    6, 11, 10,
    7, 8, 12,
    7, 12, 11,
    8, 9, 12,
    8, 9, 5,
    9, 10, 11,
    9, 11, 12,

    // X pyramid
    13, 14, 15,
    13, 15, 16,
    13, 17, 14,
    14, 17, 15,
    15, 17, 16,
    16, 17, 13,

    // X base
    18, 19, 20,
    18, 20, 21,
    18, 19, 23,
    18, 23, 22,
    19, 20, 24,
    19, 24, 23,
    20, 21, 25,
    20, 25, 24,
    21, 22, 25,
    21, 22, 18,
    22, 23, 24,
    22, 24, 25,

    // Z pyramid
    26, 27, 28,
    26, 28, 29,
    26, 30, 27,
    27, 30, 28,
    28, 30, 29,
    29, 30, 26,

    // Z base
    31, 32, 33,
    31, 33, 34,
    31, 32, 36,
    31, 36, 35,
    32, 33, 37,
    32, 37, 36,
    33, 34, 38,
    33, 38, 37,
    34, 35, 38,
    34, 35, 31,
    35, 36, 37,
    35, 37, 38,

    // Last 2 faces
    39, 31, 34,
    39, 34, 8,
    39, 19, 20,
    39, 20, 8
  });

  setAttribute("Color", std::vector<float> {
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,

    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,
    1, 0, 0, 1,

    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,

    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,

    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,

    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,

    1, 1, 1, 1
  });

  uploadAll();
}

} /* graphics */
} /* hx3d */
