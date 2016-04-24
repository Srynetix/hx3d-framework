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

#include <utility>

namespace hx3d {
namespace graphics {

Font::Font(std::string fontPath, int characterSize):
  shader(Core::Assets()->get<Shader>("text")) {
  file = File::loadBinaryFile(fontPath);

  defaultSize = characterSize;
  createFontSize(characterSize);
}

Font::~Font() {
  // Cleanup fonts and atlases
  for (auto& pair: data) {
    auto& d = pair.second;
    texture_atlas_delete(d.atlas);
    texture_font_delete(d.font);
  }
}

void Font::createFontSize(int size) {
  if (data.find(size) == data.end()) {
    texture_atlas_t* atlas = texture_atlas_new(512, 512, 1);
    texture_font_t* font = texture_font_new_from_memory(atlas, size, file->getData(), file->getSize());

    Data d;
    d.atlas = atlas;
    d.font = font;

    data.emplace(std::make_pair(size, d));
  }
}

Font::Data& Font::getFontData(int size) {
  if (data.find(size) == data.end()) {
    createFontSize(size);
  }

  return data[size];
}

unsigned int Font::getDefaultSize() const {
  return defaultSize;
}

const Ptr<Shader>& Font::getShader() {
  return shader;
}

} /* graphics */
} /* hx3d */
