/*
    Buffer attribute.
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

#ifndef HX3D_GRAPHICS_BUFFERS_ATTRIBUTE
#define HX3D_GRAPHICS_BUFFERS_ATTRIBUTE

#include "hx3d/graphics/gl.hpp"

#include <string>

namespace hx3d {
namespace graphics {
namespace buffers {

/**
@brief OpenGL buffer attribute.
*/
class Attribute {
public:

  /**
  @brief Construct an empty attribute.
  */
  Attribute();

  /**
  @brief Construct a buffer attribute.

  @param name   Attribute name (in the shader)
  @param type   Attribute type (GL_FLOAT, etc.)
  @param size   Attribute size (1, 2, 3, 4)
  */
  Attribute(const std::string name, const GLenum type, const GLuint size);

  /**
  @brief Get the attribute name

  @return Name
  */
  std::string getName() const;

  /**
  @brief Get the attribute type

  @return Type
  */
  GLenum getType() const;

  /**
  @brief Get the attribute size

  @return Size
  */
  GLuint getSize() const;

private:
  /// @brief Name
  std::string _name;
  /// @brief Type
  GLenum _type;
  /// @brief Size
  GLuint _size;
};

} /* buffers */
} /* graphics */
} /* hx3d */

#endif
