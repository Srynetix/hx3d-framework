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

#ifndef HX3D_GRAPHICS_BUFFERS_INDEXARRAYBUFFER
#define HX3D_GRAPHICS_BUFFERS_INDEXARRAYBUFFER

#include "hx3d/graphics/buffers/array_buffer.hpp"

namespace hx3d {

class IndexArrayBuffer: public ArrayBuffer<GLushort> {

public:
  /**
  Build an empty index buffer.
  */
  IndexArrayBuffer();
  ~IndexArrayBuffer();

  /**
  Build an index buffer with values.

  @param values Values
  */
  IndexArrayBuffer(std::vector<GLushort> values);

  virtual void upload() override;
  virtual void begin(Ptr<Shader> shader) override;
  virtual void end(Ptr<Shader> shader) override;
};

} /* hx3d */

#endif
