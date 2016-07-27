/*
    OpenGL Error
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

#include "hx3d/graphics/error.hpp"

#include "hx3d/graphics/gl.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace graphics {

  void checkGLError(const char* file, int line) {
    GLenum err = GL_NO_ERROR;
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::string msg;
      switch (err) {
        case GL_INVALID_ENUM:
          msg = "Invalid enum.";
          break;
        case GL_INVALID_VALUE:
          msg = "Invalid value.";
          break;
        case GL_INVALID_OPERATION:
          msg = "Invalid operation.";
          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
          msg = "Invalid framebuffer operation.";
          break;
        case GL_OUT_OF_MEMORY:
          msg = "Out of memory";
          break;
        default:
          msg = "Unknown";
      }

      auto Log = Logger::getLogger("graphics");
      Log.Error("GL Error: %s / File: %s / Line: %d", msg.c_str(), file, line);
    }
  }

} /* graphics */
} /* hx3d */
