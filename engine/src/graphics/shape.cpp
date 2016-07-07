/*
    Shape.
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

#include "hx3d/graphics/shape.hpp"

#include "hx3d/graphics/geometries/quad_geometry.hpp"
#include "hx3d/graphics/drawers/simple_shape_batch_drawer.hpp"
#include "hx3d/graphics/texture.hpp"

namespace hx3d {
namespace graphics {

Shape::Shape():
Mesh() {
  _geometry = Make<QuadGeometry>();
  _geometry->setFaceCulling(Culling::Back);

  _batchDrawer = Make<SimpleShapeBatchDrawer>();

  _borderColor = Color(255, 0, 0);
  _borderWidth = 1.f;

  setTint(Color::White);
}

void Shape::setBorderWidth(float width) {
  _borderWidth = width;
}

float Shape::getBorderWidth() const {
  return _borderWidth;
}

Color& Shape::getBorderColor() {
  return _borderColor;
}

void Shape::setBorderColor(Color color) {
  _borderColor = color;
}

void Shape::draw(const Pointer<Shader>& shader) {
  Texture::use(Texture::Blank);
  Mesh::draw(shader);
  Texture::disable();
}

} /* graphics */
} /* hx3d */
