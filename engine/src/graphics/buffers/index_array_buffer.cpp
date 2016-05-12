/*
    Index array buffer.
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

#include "hx3d/graphics/buffers/index_array_buffer.hpp"

namespace hx3d {
namespace graphics {
namespace buffers {

IndexArrayBuffer::IndexArrayBuffer():
  ArrayBuffer<GLushort>()
{}

IndexArrayBuffer::IndexArrayBuffer(const std::vector<GLushort> values):
  ArrayBuffer<GLushort>()
{
  set(values);
}

IndexArrayBuffer::~IndexArrayBuffer()
{}

void IndexArrayBuffer::upload() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _vector.size() * sizeof(GLushort), _vector.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexArrayBuffer::begin(const Pointer<Shader>& shader) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buf);
  glDrawElements(GL_TRIANGLES, _vector.size(), GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexArrayBuffer::end(const Pointer<Shader>& shader)
{}

} /* buffers */
} /* graphics */
} /* hx3d */
