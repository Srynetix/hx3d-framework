/*
    Base buffer.
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

#ifndef HX3D_GRAPHICS_UTILS_BUFFER
#define HX3D_GRAPHICS_UTILS_BUFFER

#include <vector>
#include <algorithm>

#include "hx3d/graphics/gl.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace hx3d {

template <class T>
class Buffer {

public:
  Buffer();
  virtual ~Buffer();

  /**
  Set the buffer values.

  @param values Values
  */
  void set(std::vector<T> values);

  /**
  Add buffer values.

  @param values Values
  */
  void add(std::vector<T> values);

  /**
  Get the buffer values.

  @return Values
  */
  T* data();

  /**
  Get the buffer ID.

  @return ID
  */
  GLuint getId();

  /**
  Get the buffer size.

  @return Buffer size
  */
  unsigned int size();

  /**
  Get the vector.

  @return Vector
  */
  std::vector<T>& getVector();

  /**
  Get a value.

  @param i Position
  @return Value
  */
  T getValue(unsigned int i);

  /**
  Set a value.

  @param i Position
  @param value Value
  */
  void setValue(unsigned int i, T value);

  /**
  Clear all values.
  */
  void clear();

protected:
  std::vector<T> _vector;
  GLuint _buf;
};

#include "hx3d/graphics/utils/inline/buffer.inl.hpp"

} /* hx3d */

#endif
