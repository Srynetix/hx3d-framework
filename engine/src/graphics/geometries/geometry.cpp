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

#include "hx3d/graphics/geometries/geometry.hpp"

namespace hx3d {
namespace graphics {

Geometry::Geometry(): _cullingType(Culling::Disabled) {
  addAttribute("Position", Attribute("a_position", GL_FLOAT, 3));
  addAttribute("Color", Attribute("a_color", GL_FLOAT, 4));
  addAttribute("Texture", Attribute("a_texture", GL_FLOAT, 2));
  addAttribute("Normal", Attribute("a_normal", GL_FLOAT, 3));
}

Geometry::~Geometry() {}

void Geometry::addAttribute(std::string name, Attribute attribute) {
  _attributes[name].create(attribute);
}

void Geometry::setAttribute(std::string name, std::vector<float> values) {
  _attributes[name].set(values);
}

AttributeArrayBuffer& Geometry::getAttribute(std::string name) {
  return _attributes[name];
}

std::map<std::string, AttributeArrayBuffer>& Geometry::getAttributes() {
  return _attributes;
}

void Geometry::setIndices(std::vector<GLushort> values) {
  _indices.set(values);
}

IndexArrayBuffer& Geometry::getIndices() {
  return _indices;
}

void Geometry::setFaceCulling(Culling culling) {
  _cullingType = culling;
}

Culling& Geometry::getFaceCulling() {
  return _cullingType;
}

void Geometry::uploadAll() {
  VertexArray::use(_array);

  for (auto& a: _attributes) {
    a.second.upload();
  }

  _indices.upload();

  VertexArray::disable();
}

} /* graphics */
} /* hx3d */
