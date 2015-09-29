/*
    Multi array buffer.
    One buffer for multiple attributes.

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

#include "hx3d/graphics/buffers/multi_array_buffer.hpp"
#include "hx3d/utils/log.hpp"

#include "hx3d/graphics/shader.hpp"

namespace hx3d {

MultiArrayBuffer::MultiArrayBuffer():
  ArrayBuffer<float>()
{}

MultiArrayBuffer::~MultiArrayBuffer()
{}

void MultiArrayBuffer::addAttribute(std::string name, Attribute attribute) {

  if (_attributes.find(name) != _attributes.end()) {
    Log.Error("MultiArrayBuffer: Attribute %s already exists.", name.c_str());
    return;
  }

  _attributes[name].create(attribute);
}

void MultiArrayBuffer::setAttribute(std::string name, std::vector<float> data) {
  if (_attributes.find(name) != _attributes.end()) {
    _attributes[name].set(data);
  }
}

AttributeArrayBuffer& MultiArrayBuffer::getAttribute(std::string name) {
  return _attributes[name];
}

void MultiArrayBuffer::generate()
{
  unsigned int totalLength = 0;
  for (unsigned int i = 0; i < _attributes.size(); ++i) {
    AttributeArrayBuffer& buffer = getMapAttribute(i);
    totalLength += buffer.size();
  }

  _vector.clear();
  _vector.resize(totalLength);

  unsigned int last = 0;
  for (unsigned int i = 0; i < _attributes.size(); ++i) {
    AttributeArrayBuffer& buffer = getMapAttribute(i);
    for (unsigned int j = 0; j < buffer.size(); ++j) {
      _vector[last++] = buffer.getValue(j);
    }
  }
}

void MultiArrayBuffer::upload() {
  generate();

  glBindBuffer(GL_ARRAY_BUFFER, _buf);
  glBufferData(GL_ARRAY_BUFFER, _vector.size() * sizeof(float), _vector.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MultiArrayBuffer::begin(Ptr<Shader> shader)
{
  glBindBuffer(GL_ARRAY_BUFFER, _buf);

  unsigned int lastSize = 0;
  for (auto& attr: _attributes) {
    Attribute& attribute = attr.second.getAttribute();
    GLint loc = shader->getAttribute(attribute.getName());
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, attribute.getSize(), attribute.getType(), GL_FALSE, 0, BUFFER_OFFSET(lastSize * sizeof(float)));
    lastSize += attr.second.size();
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MultiArrayBuffer::end(Ptr<Shader> shader)
{
  for (auto& attr: _attributes) {
    Attribute& attribute = attr.second.getAttribute();

    GLint loc = shader->getAttribute(attribute.getName());
    glDisableVertexAttribArray(loc);
  }
}

//////////////////////////

AttributeArrayBuffer& MultiArrayBuffer::getMapAttribute(unsigned int i) {

  unsigned int count = 0;
  for (auto it = _attributes.begin(); it != _attributes.end(); ++it, ++count) {
    if (count == i) {
      return it->second;
    }
  }

  throw std::out_of_range("Out of range");
}

unsigned int MultiArrayBuffer::attributeTotalSize() {
  unsigned int totalsize = 0;
  for (auto& attr: _attributes) {
    Attribute& attribute = attr.second.getAttribute();
    totalsize += attribute.getSize();
  }

  return totalsize;
}

} /* hx3d */
