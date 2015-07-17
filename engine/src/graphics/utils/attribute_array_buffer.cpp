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

#include "hx3d/graphics/utils/attribute_array_buffer.hpp"

#include "hx3d/graphics/shader.hpp"

namespace hx3d {

AttributeArrayBuffer::AttributeArrayBuffer():
  ArrayBuffer<float>(), _attribute(""), _type(GL_FLOAT), _attributeSize(0)
{}

AttributeArrayBuffer::AttributeArrayBuffer(std::string attribute, GLenum type, GLuint attributeSize):
  ArrayBuffer<float>(), _attribute(attribute), _type(type), _attributeSize(attributeSize)
{}

AttributeArrayBuffer::AttributeArrayBuffer(std::string attribute, GLenum type, GLuint attributeSize, std::vector<float> values):
  AttributeArrayBuffer(attribute, type, attributeSize)
{
  set(values);
}

AttributeArrayBuffer::~AttributeArrayBuffer() {}

void AttributeArrayBuffer::create(std::string attribute, GLenum type, GLuint attributeSize) {
  _attribute = attribute;
  _type = type;
  _attributeSize = attributeSize;
}

void AttributeArrayBuffer::upload() {

  if (_vector.size() > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, _buf);
    glBufferData(GL_ARRAY_BUFFER, _vector.size() * sizeof(float), _vector.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
}

void AttributeArrayBuffer::begin(Ptr<Shader> shader) {

  if (_vector.size() > 0) {
    GLint loc = shader->getAttribute(_attribute);

    glBindBuffer(GL_ARRAY_BUFFER, _buf);
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, _attributeSize, _type, GL_FALSE, 0, BUFFER_OFFSET(0));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
}

void AttributeArrayBuffer::end(Ptr<Shader> shader) {
  if (_vector.size() > 0) {
    GLint loc = shader->getAttribute(_attribute);

    glDisableVertexAttribArray(loc);
  }
}

} /* hx3d */
