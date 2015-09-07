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

#ifndef HX3D_GRAPHICS_IMAGE
#define HX3D_GRAPHICS_IMAGE

#include "hx3d/graphics/color.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Texture;
class Image {
public:

  /**
  Construct an empty image.
  Use @link#create to create the image.
  */
  Image();

  /**
  Construct an image with a width and height.
  @param width Width
  @param height Height
  */
  Image(unsigned int width, unsigned int height);
  ~Image();

  /**
  Initialize an image.
  @param width Width
  @param height Height
  */
  void create(unsigned int width, unsigned int height);

  /**
  Set a pixel with a color.
  @param x      X coordinate
  @param y      Y coordinate
  @param color  Color
  */
  void set(unsigned int x, unsigned int y, Color color);

  /**
  Set a rectangle with a color.
  @param x      X coordinate
  @param y      Y coordinate
  @param w      Width
  @param h      Height
  @param color  Color
  */
  void setRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Color color);

  /**
  Get a pixel color.
  @param x X coordinate
  @param y Y coordinate
  @return Color
  */
  Color get(unsigned int x, unsigned int y);

  /**
  Get the texture.
  @return Texture (Ptr)
  */
  Ptr<Texture> getTexture();

  /**
  Get the image width.
  @return Width
  */
  unsigned int getWidth();

  /**
  Get the image height.
  @return Height
  */
  unsigned int getHeight();

  /**
  Recreate a texture from the image.
  */
  void buildTexture();

  /**
  Update an existing texture zone.
  @param x X coordinate
  @param y Y coordinate
  @param w Width
  @param h Height
  */
  void updateTextureZone(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

  friend class Texture;

private:
  unsigned int _width;
  unsigned int _height;

  unsigned char* _buffer;

  Ptr<Texture> _texture;
};

} /* hx3d */

#endif
