/*
    Base VBO.
    Contains one index array buffer and multiple attributes array buffers.

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

#include "hx3d/graphics/utils/vbo.hpp"

#include "hx3d/graphics/shader.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {

VBO::VBO() {}

VBO::~VBO() {}

void VBO::uploadAll() {
  for (auto& pair: attributes) {
      pair.second.upload();
  }

  indices.upload();
}

void VBO::uploadIndices() {
  indices.upload();
}

void VBO::uploadAttribute(std::string name) {
  if (attributes.find(name) != attributes.end()) {
    attributes[name].upload();
  }
}

void VBO::draw(Ptr<Shader> shader) {

  if (!shader) {
    Log.Error("Attempt to draw VBO without shader.");
    return;
  }

  for (auto& pair: attributes) {
    pair.second.begin(shader);
  }

  indices.begin(shader);
  indices.end(shader);

  for (auto& pair: attributes) {
    pair.second.end(shader);
  }
}

void VBO::addAttribute(std::string name, std::string shaderName, GLenum type, GLuint size) {
  if (attributes.find(name) != attributes.end()) {
    Log.Error("Attribute %s already exists.", name.c_str());
    return;
  }

  attributes[name].create(shaderName, type, size);
}

void VBO::setAttribute(std::string name, std::vector<float> data) {
  if (attributes.find(name) != attributes.end()) {
    attributes[name].set(data);
  }
}

AttributeArrayBuffer& VBO::getAttribute(std::string name) {
  return attributes[name];
}

void VBO::setIndices(std::vector<GLushort> data) {
  indices.set(data);
}

IndexArrayBuffer& VBO::getIndices() {
  return indices;
}

} /* hx3d */
