/*
    Texture region.
    To delimit a texture rectangle.

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

#ifndef HX3D_GRAPHICS_TEXTUREREGION
#define HX3D_GRAPHICS_TEXTUREREGION

#include <glm/vec2.hpp>

#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace graphics {

class Texture;

/**
@brief Defines a rectangle in a texture.
*/
class TextureRegion {

public:
  /**
  @brief Create a texture region from a texture and rectangle coordinates.

  @param texture  Texture (Ptr)
  @param minX     Left coordinate
  @param maxX     Width
  @param minY     Top coordinate
  @param maxY     Height
  */
  TextureRegion(Ptr<Texture> texture, float minX, float maxX, float minY, float maxY);

  /**
  @brief Create an empty texture region
  */
  TextureRegion();

  /**
  @brief Get the texture

  @return Texture (Ptr)
  */
  const Ptr<Texture>& getTexture();

  /**
  @brief Get the left coordinate

  @return Min X
  */
  float getMinX();

  /**
  @brief Get the right coordinate

  @return Max X
  */
  float getMaxX();

  /**
  @brief Get the bottom coordinate

  @return Min Y
  */
  float getMinY();

  /**
  @brief Get the top coordinate

  @return Max Y
  */
  float getMaxY();

  /**
  @brief Get the region width

  @return Width
  */
  float getWidth();

  /**
  @brief Get the region height

  @return Height
  */
  float getHeight();

private:
  /// @brief Texture
  Ptr<Texture> _texture;
  /// @brief Left coordinate
  float _minX;
  /// @brief Right coordinate
  float _maxX;
  /// @brief Bottom coordinate
  float _minY;
  /// @brief Top coordinate
  float _maxY;

  /// @brief Converted UV coordinates
  glm::vec2 _uv;
};

} /* graphics */
} /* hx3d */

#endif
