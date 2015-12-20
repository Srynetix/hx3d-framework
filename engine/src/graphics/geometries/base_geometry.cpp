/*
    Base geometry.
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

#include "hx3d/graphics/geometries/base_geometry.hpp"

namespace hx3d {

BaseGeometry::BaseGeometry() {
  addAttribute("Position", Attribute("a_position", GL_FLOAT, 3));
  addAttribute("Color", Attribute("a_color", GL_FLOAT, 4));
  addAttribute("Texture", Attribute("a_texture", GL_FLOAT, 2));
}

void BaseGeometry::addAttribute(std::string name, Attribute attribute) {
  _attributes[name].create(attribute);
}

void BaseGeometry::setAttribute(std::string name, std::vector<float> values) {
  _attributes[name].set(values);
}

AttributeArrayBuffer& BaseGeometry::getAttribute(std::string name) {
  return _attributes[name];
}

void BaseGeometry::setIndices(std::vector<GLushort> values) {
  _indices.set(values);
}

IndexArrayBuffer& BaseGeometry::getIndices() {
  return _indices;
}

void BaseGeometry::uploadAll() {
  for (auto& a: _attributes) {
    a.second.upload();
  }

  _indices.upload();
}

} /* hx3d */
