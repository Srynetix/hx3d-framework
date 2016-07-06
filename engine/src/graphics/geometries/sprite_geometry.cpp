/*
    Sprite model.
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

#include "hx3d/graphics/geometries/sprite_geometry.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/texture_region.hpp"

namespace hx3d {
namespace graphics {

SpriteGeometry::SpriteGeometry(): QuadGeometry() {}

void SpriteGeometry::activateFramebufferMode() {
  setAttribute("Texture", std::vector<float> {
    1, 0,
    0, 0,
    0, 1,
    1, 1
  });
}

void SpriteGeometry::activateTextureMode() {
  setAttribute("Texture", std::vector<float> {
    0, 0,
    1, 0,
    1, 1,
    0, 1
  });
}

void SpriteGeometry::setFromRegion(const Pointer<TextureRegion>& region) {

  // Calculate texture points;
  unsigned int width = region->getTexture()->getWidth();
  unsigned int height = region->getTexture()->getHeight();

  setAttribute("Texture", std::vector<float> {
    region->getMinX() / (float)width, region->getMinY() / float(height),
    region->getMaxX() / (float)width, region->getMinY() / float(height),
    region->getMaxX() / (float)width, region->getMaxY() / float(height),
    region->getMinX() / (float)width, region->getMaxY() / float(height)
  });
}

} /* graphics */
} /* hx3d */
