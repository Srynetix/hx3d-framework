/*
    Framebuffer.
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

#ifndef HX3D_GRAPHICS_FRAMEBUFFER
#define HX3D_GRAPHICS_FRAMEBUFFER

#include "hx3d/graphics/gl.hpp"
#include "hx3d/graphics/color.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace graphics {

class Texture;

/**
@brief Render-to-texture buffer.
*/
class Framebuffer {

public:
  /**
  @brief Create a framebuffer at screen size.
  */
  Framebuffer();
  ~Framebuffer();

  /**
  @brief Create a framebuffer.

  @param width  Width
  @param height Height
  */
  Framebuffer(unsigned int width, unsigned int height);

  /**
  @brief Get the framebuffer color buffer.

  @return Texture (Ptr)
  */
  Ptr<Texture> getColorBuffer();

  /**
  @brief Resize the framebuffer.

  @param width Width
  @param height Height
  */
  void resize(unsigned int width, unsigned int height);

  /////////////////

  /**
  @brief Fetch the default framebuffer of the application.
  */
  static void fetchDefaultFramebuffer();

  /**
  @brief Use the framebuffer as current framebuffer.

  @param buf Framebuffer
  */
  static void use(const Ptr<Framebuffer>& buf);

  /**
  @brief Use the default framebuffer.
  */
  static void useDefault();

  /**
  @brief Get the current framebuffer
  */
  static Ptr<Framebuffer> getCurrentFramebuffer();

  /**
  @brief Clear the framebuffer.
  */
  static void clear(Color color);

private:
  /// @brief Framebuffer width
  unsigned int _width;
  /// @brief Framebuffer height
  unsigned int _height;

  /// @brief Framebuffer ID
  GLuint _id;
  /// @brief Color buffer
  Ptr<Texture> _colorBuffer;
  /// @brief Depth buffer
  GLuint _depthBuffer;

  /// @brief Default framebuffer ID
  static GLint _defaultID;

  static Ptr<Framebuffer> _currentFramebuffer;

  /**
  @brief Create an empty framebuffer.
  */
  void create();

  /**
  @brief Create a render buffer.

  @param id     Buffer id
  @param format Buffer format
  */
  void createRenderBuffer(GLuint& id, GLenum format);
};

} /* graphics */
} /* hx3d */

#endif
