/*
    Mesh geometry drawer.
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

#include "hx3d/graphics/drawers/mesh_drawer.hpp"

#include "hx3d/graphics/geometries/geometry.hpp"
#include "hx3d/graphics/shader.hpp"

namespace hx3d {
namespace graphics {

MeshDrawer::MeshDrawer(): GeometryDrawer() {}

void MeshDrawer::drawWithShader(const Pointer<Geometry>& geom, const Pointer<Shader>& shader, const GLenum drawPrimitive) {

  // Culling
  switch (geom->getFaceCulling()) {
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
  }

  VertexArray::use(geom->getVertexArray());
  auto& indices = geom->getIndices();

  if (indices.size() == 0) {
    glDrawArrays(drawPrimitive, 0, geom->getAttributeBuffer("Position").size());
  } else {
    indices.draw(drawPrimitive);
  }

  VertexArray::disable();
}

} /* graphics */
} /* hx3d */
