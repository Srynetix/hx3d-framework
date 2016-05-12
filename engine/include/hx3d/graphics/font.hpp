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
#include <map>

#include "hx3d/graphics/shader.hpp"
#include "hx3d/utils/resource.hpp"
#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/file.hpp"

namespace hx3d {
namespace graphics {

/**
@brief Font management.
*/
class Font: public Resource {
public:

  /**
  @brief Internal font data
  */
  struct Data {
    /// @brief Internal font
    texture_font_t* font;
    /// @brief Internal atlas
    texture_atlas_t* atlas;
  };

  /**
  @brief Build a font from a path and a character size.

  @param fontPath       Path to font
  @param characterSize  Character size
  */
  Font(std::string fontPath, int characterSize);
  ~Font();

  /**
  @brief Generate a font in cache.

  @param size Font size
  */
  void createFontSize(int size);

  /**
  @brief Get internal font data from a size.

  If it does not exists, creates it with @link createFontSize @endlink.

  @param size Font size

  @return Internal font data
  */
  Data& getFontData(int size);

  /**
  @brief Get the default font size

  @return Default font size
  */
  unsigned int getDefaultSize() const;

  /**
  @brief Get the font shader

  @return Shader (Ptr)
  */
  const Pointer<Shader>& getShader();

private:
  /// @brief Font shader
  Pointer<Shader> shader;
  /// @brief Font file
  Pointer<File> file;

  /// @brief Internal font data map
  std::map<int, Data> data;

  /// @brief Default font size
  unsigned int defaultSize;
};

} /* graphics */
} /* hx3d */

#endif
