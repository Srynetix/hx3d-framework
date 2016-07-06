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

#pragma once

#include <vector>

#include "hx3d/graphics/gl.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace hx3d {
namespace graphics {

/**
@brief Data buffer helpers.
*/
namespace buffers {

/**
@brief OpenGL data buffer.
*/
template <class T>
class Buffer {

public:
  Buffer();
  virtual ~Buffer();

  /**
  @brief Set the buffer values.

  @param values Values
  */
  void set(const std::vector<T>& values);

  /**
  @brief Add buffer values.

  @param values Values
  */
  void add(const std::vector<T>& values);

  /**
  @brief Get the buffer values.

  @return Values
  */
  T* data();

  /**
  @brief Get the buffer ID.

  @return ID
  */
  GLuint getId();

  /**
  @brief Get the buffer size.

  @return Buffer size
  */
  unsigned int size();

  /**
  @brief Get the vector.

  @return Vector
  */
  std::vector<T>& getVector();

  /**
  @brief Get a value.

  @param i Position

  @return Value
  */
  T getValue(unsigned int i);

  /**
  @brief Set a value.

  @param i Position
  @param value Value
  */
  void setValue(const unsigned int i, const T value);

  /**
  @brief Clear all values.
  */
  void clear();

protected:
  /// @brief Data
  std::vector<T> _vector;
  /// @brief Internal ID
  GLuint _buf;
};

} /* buffers */
} /* graphics */
} /* hx3d */

#include "hx3d/graphics/buffers/_inline/buffer.inl.hpp"
