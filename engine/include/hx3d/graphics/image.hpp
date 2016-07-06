/*
    32-bit image.
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

#pragma once

#include "hx3d/graphics/color.hpp"
#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace graphics {

class Texture;

/**
@brief Real-time editable texture.
*/
class Image {
public:

  /**
  @brief Construct an empty image.
  Use @link create @endlink to create the image.
  */
  Image();

  /**
  @brief Construct an image with a width and height.

  @param width Width
  @param height Height
  */
  Image(unsigned int width, unsigned int height);
  ~Image();

  /**
  @brief Initialize an image.

  @param width Width
  @param height Height
  */
  void create(unsigned int width, unsigned int height);

  /**
  @brief Set a pixel with a color.

  @param x      X coordinate
  @param y      Y coordinate
  @param color  Color
  */
  void set(unsigned int x, unsigned int y, Color color);

  /**
  @brief Set a rectangle with a color.

  @param x      X coordinate
  @param y      Y coordinate
  @param w      Width
  @param h      Height
  @param color  Color
  */
  void setRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Color color);

  /**
  @brief Get a pixel color.

  @param x X coordinate
  @param y Y coordinate

  @return Color
  */
  Color get(unsigned int x, unsigned int y);

  /**
  @brief Get the texture.

  @return Texture (Ptr)
  */
  Pointer<Texture> getTexture();

  /**
  @brief Get the image width.

  @return Width
  */
  unsigned int getWidth();

  /**
  @brief Get the image height.

  @return Height
  */
  unsigned int getHeight();

  /**
  @brief Recreate a texture from the image.
  */
  void buildTexture();

  /**
  @brief Update an existing texture zone.

  @param x X coordinate
  @param y Y coordinate
  @param w Width
  @param h Height
  */
  void updateTextureZone(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

  friend class Texture;

private:
  /// @brief Image width
  unsigned int _width;
  /// @brief Image height
  unsigned int _height;
  /// @brief Color buffer
  unsigned char* _buffer;

  /// @brief Internal texture
  Pointer<Texture> _texture;
};

} /* graphics */
} /* hx3d */
