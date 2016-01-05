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

#ifndef HX3D_GRAPHICS_GEOMETRIES_SPRITEGEOMETRY
#define HX3D_GRAPHICS_GEOMETRIES_SPRITEGEOMETRY

#include "hx3d/graphics/geometries/geometry.hpp"
#include "hx3d/graphics/texture_region.hpp"

namespace hx3d {
namespace graphics {
namespace geom {

/**
@brief Sprite defined VBO geometry
*/
class SpriteGeometry: public Geometry {

public:
  SpriteGeometry();

  /**
  @brief Prepare the sprite for render-to-texture mode.
  */
  void activateFramebufferMode();

  /**
  @brief Prepare the sprite for simple texture mode.
  */
  void activateTextureMode();

  /**
  @brief Set the geometry for a texture region.
  */
  void setFromRegion(TextureRegion& region);
};

} /* geom */
} /* graphics */
} /* hx3d */

#endif
