/*
    Simple math function.
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

#ifndef HX3D_MATH_FUNCTION
#define HX3D_MATH_FUNCTION

#include <glm/vec2.hpp>
#include <functional>

namespace hx3d {
namespace math {

/**
@brief Math function definition
*/
class Function {

public:
  /**
  @brief Create a function from an initial time value, speed and a math function.

  The math function takes 3 parameters:
  - X coordinate (inout)
  - Y coordinate (inout)
  - Time (in)

  @param init   Initial time value
  @param speed  Speed
  @param func   Math function
  */
  Function(float init, float speed, std::function<void(float&, float&, float)> func);

  /**
  @brief Empty function.
  */
  Function();

  /**
  @brief Enable function.
  */
  void enable();

  /**
  @brief Disable function
  */
  void disable();

  /**
  @brief Is the function enabled ?

  @return True/False
  */
  bool isEnabled();

  /**
  @brief Reset the function time.
  */
  void reset();

  /**
  @brief Set init value.

  @param init Init value
  */
  void setInit(float init);

  /**
  @brief Step the function time.
  */
  void step();

  /**
  @brief Sample the current coordinates from the math function.

  @return Coordinates (vec2)
  */
  glm::vec2 sample();

private:
  /// @brief Init X value
  float _init;
  /// @brief Speed value
  float _speed;
  /// @brief Current time
  float _t;
  /// @brief Enabled
  bool _enabled;

  /// @brief Function
  std::function<void(float&, float&, float)> _func;
};

} /* math */
} /* hx3d */

#endif
