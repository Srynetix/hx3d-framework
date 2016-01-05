/*
    Stencil buffer management.
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

#ifndef HX3D_GRAPHICS_STENCIL
#define HX3D_GRAPHICS_STENCIL

#include "hx3d/graphics/gl.hpp"

namespace hx3d {
namespace graphics {

/**
@brief 2D stencil drawing.

Use this to hide/show elements following a shape or to apply a function over a specified shape.
*/
class Stencil {
public:
  /**
  @brief Stencil function
  */
  enum class Function {
    /// @brief Never hide
    Never = 0,
    /// @brief Always hide
    Always,
    /// @brief Hide when it's equal
    Equal,
    /// @brief Hide when it's not equal
    NotEqual,
    /// @brief Hide when it's less
    Less,
    /// @brief Hide when it's greater
    Greater,
    /// @brief Hide when it's less or equal
    LessOrEqual,
    /// @brief Hide when it's greater or equal
    GreaterOrEqual
  };

  /**
  @brief Stencil operation
  */
  enum class Operation {
    /// @brief Do nothing
    Keep = 0,
    /// @brief Remove
    Zero,
    /// @brief Replace
    Replace,
    /// @brief Increment
    Increment,
    /// @brief Increment and wrap
    IncrementWrap,
    /// @brief Decrement
    Decrement,
    /// @brief Decrement and wrap
    DecrementWrap,
    /// @brief Invert
    Invert
  };

  /**
  @brief Enable stencil mode.
  */
  static void enable();

  /**
  @brief Disable stencil mode.
  */
  static void disable();

  /**
  @brief Set the stencil function.

  @param func Function
  @param ref  Ref
  @param mask Mask
  */
  void setFunction(Function func, int ref, int mask);

  /**
  @brief Set the stencil operation.

  @param sfail  Operation when the stencil function fail
  @param dpfail Operation when the depth buffer test fail
  @param dppass Operation when the depth buffer test pass
  */
  void setOperation(Operation sfail, Operation dpfail, Operation dppass);

  /**
  @brief Begin to use the stencil.
  */
  void begin();

  /**
  @brief End the stencil.
  */
  void end();

private:
  /**
  @brief Convert the function type to OpenGL.

  @param func Stencil function

  @return GLenum
  */
  GLenum convertFunction(Function func);
  /**
  @brief Convert the operation type to OpenGL.

  @param op Stencil operation

  @return GLenum
  */
  GLenum convertOperation(Operation op);
};

} /* graphics */
} /* hx3d */

#endif
