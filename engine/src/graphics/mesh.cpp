/*
    Mesh.
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

#include "hx3d/graphics/mesh.hpp"

#include "hx3d/graphics/texture.hpp"

namespace hx3d {
namespace graphics {

Mesh::Mesh() {}

void Mesh::draw(const Ptr<Shader>& shader) {

  if (_geometry->getAttribute("Texture").size() == 0) {
    Texture::use(Texture::Blank);
    _geometry->draw(shader);
    Texture::disable();
  }

  else {
    _geometry->draw(shader);
  }
}

void Mesh::setTint(Color tint) {
  _tint = tint;

  updateColor();
}

void Mesh::setGeometry(const Ptr<geom::BaseGeometry>& geometry) {
  _geometry = geometry;
}

Ptr<geom::BaseGeometry>& Mesh::getGeometry() {
  return _geometry;
}

void Mesh::updateColor() {

  glm::vec4 floatColor = _tint.toFloat();

  AttributeArrayBuffer& colors = _geometry->getAttribute("Color");
  float* colorsData = colors.data();
    if (colorsData[0] == floatColor.r
      && colorsData[1] == floatColor.g
      && colorsData[2] == floatColor.b
      && colorsData[3] == floatColor.a)
      return;

    for (unsigned int i = 0; i < colors.size(); i += 4) {
      colorsData[i] = floatColor.r;
      colorsData[i+1] = floatColor.g;
      colorsData[i+2] = floatColor.b;
      colorsData[i+3] = floatColor.a;
    }

  _geometry->uploadAll();
}

Color& Mesh::getTint() {
  return _tint;
}

} /* graphics */
} /* hx3d */
