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

#ifndef HX3D_GRAPHICS_UTILS_ARRAYBUFFER
#define HX3D_GRAPHICS_UTILS_ARRAYBUFFER

#include "hx3d/graphics/utils/buffer.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Shader;

template <class T>
class ArrayBuffer: public Buffer<T> {

public:
  ArrayBuffer();
  virtual ~ArrayBuffer();

  /**
  Upload the data to the GPU.
  */
  virtual void upload() = 0;

  /**
  Begin the use with a shader.
  @param shader Shader (Ptr)
  */
  virtual void begin(Ptr<Shader> shader) = 0;

  /**
  End the use with a shader.
  @parm shader Shader (Ptr)
  */
  virtual void end(Ptr<Shader> shader) = 0;
};

#include "hx3d/graphics/utils/array_buffer.inl.hpp"

} /* hx3d */

#endif
