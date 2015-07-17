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

#include "hx3d/graphics/font.hpp"

#include "hx3d/graphics/shader.hpp"

#include "hx3d/core/core.hpp"

#include "hx3d/utils/assets.hpp"
#include "hx3d/utils/file.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {

Font::Font(std::string fontPath, int characterSize):
  shader(Core::Assets()->get<Shader>("text")), font(nullptr) {

  atlas = texture_atlas_new(512, 512, 1);
  file = File::loadBinaryFile(fontPath);

  font = texture_font_new_from_memory(atlas, characterSize, file->data, file->size);
  if (font == nullptr) {
    Log.Error("Error while loading font `%s`.", fontPath.c_str());
  } else {
    Log.Info("Font `%s` loaded.", fontPath.c_str());
  }
}

} /* hx3d */
