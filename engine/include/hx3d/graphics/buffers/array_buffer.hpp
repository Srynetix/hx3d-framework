/*
    Base array buffer.
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

#ifndef HX3D_GRAPHICS_BUFFERS_ARRAYBUFFER
#define HX3D_GRAPHICS_BUFFERS_ARRAYBUFFER

#include "hx3d/graphics/buffers/buffer.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace graphics {

class Shader;

namespace buffers {

/**
@brief OpenGL GPU uploadable buffer
*/
template <class T>
class ArrayBuffer: public Buffer<T> {

public:
  ArrayBuffer();
  virtual ~ArrayBuffer();

  /**
  @brief Upload the data to the GPU.
  */
  virtual void upload() = 0;

  /**
  @brief Begin the use with a shader.

  @param shader Shader (Ptr)
  */
  virtual void begin(const Ptr<Shader>& shader) = 0;

  /**
  @brief End the use with a shader.

  @param shader Shader (Ptr)
  */
  virtual void end(const Ptr<Shader>& shader) = 0;
};

} /* buffers */
} /* graphics */
} /* hx3d */

#include "hx3d/graphics/buffers/_inline/array_buffer.inl.hpp"

#endif
