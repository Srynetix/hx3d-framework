/*
    Attribute array buffer.
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

#include "hx3d/graphics/buffers/attribute_stream_buffer.hpp"

#include "hx3d/graphics/shader.hpp"

namespace hx3d {

AttributeStreamBuffer::AttributeStreamBuffer():
  ArrayBuffer<float>(), _attribute(), _stream_size(0)
{}

AttributeStreamBuffer::AttributeStreamBuffer(const Attribute attribute, const unsigned int stream_size):
  ArrayBuffer<float>(), _attribute(attribute), _stream_size(stream_size)
{}

AttributeStreamBuffer::~AttributeStreamBuffer() {}

void AttributeStreamBuffer::create(const Attribute attribute, const unsigned int stream_size) {
  _attribute = attribute;
  _stream_size = stream_size;
}

Attribute& AttributeStreamBuffer::getAttribute() {
  return _attribute;
}

void AttributeStreamBuffer::upload() {

  // if (_vector.size() > 0) {
  //   glBindBuffer(GL_ARRAY_BUFFER, _buf);
  //   glBufferData(GL_ARRAY_BUFFER, _vector.size() * sizeof(float), _vector.data(), GL_STATIC_DRAW);
  //   glBindBuffer(GL_ARRAY_BUFFER, 0);
  // }

  glBindBuffer(GL_ARRAY_BUFFER, _buf);
  glBufferData(GL_ARRAY_BUFFER, _stream_size * _attribute.getSize() * sizeof(_attribute.getType()), NULL, GL_STREAM_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AttributeStreamBuffer::begin(const Ptr<Shader>& shader) {

  GLint loc = shader->getAttribute(_attribute.getName());

  glBindBuffer(GL_ARRAY_BUFFER, _buf);
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, _attribute.getSize(), _attribute.getType(), GL_FALSE, 0, BUFFER_OFFSET(0));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AttributeStreamBuffer::end(const Ptr<Shader>& shader) {
  if (_vector.size() > 0) {
    GLint loc = shader->getAttribute(_attribute.getName());

    glDisableVertexAttribArray(loc);
  }
}

} /* hx3d */
