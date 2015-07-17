/*
    Font.
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

#ifndef HX3D_GRAPHICS_FONT
#define HX3D_GRAPHICS_FONT

#include <freetype-gl/freetype-gl.h>
#include <string>

#include "hx3d/utils/resource.hpp"
#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Shader;
class File;

class Font: public Resource {
public:
  /**
  Build a font from a path and a character size.

  @param fontPath       Path to font
  @param characterSize  Character size
  */
  Font(std::string fontPath, int characterSize);

  Ptr<Shader> shader;
  Ptr<File> file;

  texture_font_t* font;
  texture_atlas_t* atlas;
};

} /* hx3d */

#endif
