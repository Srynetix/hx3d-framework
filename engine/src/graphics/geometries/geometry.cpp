/*
    Geometry.
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

#include "hx3d/graphics/geometries/geometry.hpp"

namespace hx3d {
namespace graphics {
namespace geom {

Geometry::Geometry(): BaseGeometry() {}

void Geometry::draw(const Ptr<Shader>& shader) {

  // Culling
  switch (_cullingType) {
    case Culling::Disabled:
      glDisable(GL_CULL_FACE);
      break;
    case Culling::Front:
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
      break;
    case Culling::Back:
      glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);
      break;
    default:
      break;
  }

  for (auto& a: _attributes) {
    a.second.begin(shader);
  }

  if (_indices.size() == 0) {
    glDrawArrays(GL_TRIANGLES, 0, _attributes["Position"].size());
  } else {
    _indices.begin(shader);
    _indices.end(shader);
  }

  for (auto& a: _attributes) {
    a.second.end(shader);
  }
}

} /* geom */
} /* graphics */
} /* hx3d */
