/*
    Multi VBO.
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

#include "hx3d/graphics/utils/multi_vbo.hpp"

#include "hx3d/graphics/shader.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {

MultiVBO::MultiVBO() {}

MultiVBO::~MultiVBO() {}

void MultiVBO::uploadAll() {
  multiBuffer.upload();

  indices.upload();
}

void MultiVBO::uploadIndices() {
  indices.upload();
}

void MultiVBO::draw(Ptr<Shader> shader) {

  if (!shader) {
    Log.Error("Attempt to draw VBO without shader.");
    return;
  }

  multiBuffer.begin(shader);

  indices.begin(shader);
  indices.end(shader);

  multiBuffer.end(shader);
}

void MultiVBO::addAttribute(std::string name, Attribute attribute) {
  multiBuffer.addAttribute(name, attribute);
}

void MultiVBO::setAttribute(std::string name, std::vector<float> data) {
  multiBuffer.setAttribute(name, data);
}

AttributeArrayBuffer& MultiVBO::getAttribute(std::string name) {
  return multiBuffer.getAttribute(name);
}

void MultiVBO::setIndices(std::vector<GLushort> data) {
  indices.set(data);
}

IndexArrayBuffer& MultiVBO::getIndices() {
  return indices;
}

MultiArrayBuffer& MultiVBO::getMultiBuffer() {
  return multiBuffer;
}

} /* hx3d */
