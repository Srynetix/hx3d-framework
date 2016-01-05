/*
    Star model.
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

#include "hx3d/graphics/geometries/star_geometry.hpp"

namespace hx3d {
namespace graphics {
namespace geom {

StarGeometry::StarGeometry(): Geometry() {

  setAttribute("Position", std::vector<float> {
    -0.5f, 0.75f, -0.25f,
    0.5f, 0.75f, -0.25f,
    0.75f, 0, -0.25f,
    0, -0.75f, -0.25f,
    -0.75f, 0, -0.25f,

    -0.5f, 0.75f, 0.25f,
    0.5f, 0.75f, 0.25f,
    0.75f, 0, 0.25f,
    0, -0.75f, 0.25f,
    -0.75f, 0, 0.25f,

    0, 0, -0.5f,
    0, 0, 0.5f,

    1.5f, 0.75f, 0,
    1.25f, -1.25f, 0,
    -1.25f, -1.25f, 0,
    -1.5f, 0.75f, 0,
    0, 1.75f, 0
  });

  setIndices(std::vector<GLushort> {
    0, 1, 10,
    1, 2, 10,
    2, 3, 10,
    3, 4, 10,
    4, 0, 10,

    5, 6, 11,
    6, 7, 11,
    7, 8, 11,
    8, 9, 11,
    9, 5, 11,

    6, 12, 7,
    7, 12, 2,
    2, 12, 1,
    1, 12, 6,

    7, 13, 8,
    8, 13, 3,
    3, 13, 2,
    2, 13, 7,

    8, 14, 9,
    9, 14, 4,
    4, 14, 3,
    3, 14, 8,

    9, 15, 5,
    5, 15, 0,
    0, 15, 4,
    4, 15, 9,

    5, 16, 6,
    6, 16, 1,
    1, 16, 0,
    0, 16, 5
  });

  setAttribute("Color", std::vector<float> {
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

    0, 0, 1, 1,
    0, 0, 1, 1,

    1, 1, 0, 1,
    1, 1, 0, 1,
    1, 1, 0, 1,
    1, 1, 0, 1,
    1, 1, 0, 1
  });

  uploadAll();
}

} /* geom */
} /* graphics */
} /* hx3d */
