/*
    Texture.
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

#ifndef HX3D_GRAPHICS_TEXTURE
#define HX3D_GRAPHICS_TEXTURE

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/resource.hpp"

#include "hx3d/graphics/gl.hpp"

#include <string>

namespace hx3d {

class Font;
class Texture: public Resource {
public:

  enum class FilterType {
    Min,
    Max
  };

  enum class FilterValue {
    Linear,
    Nearest
  };

  static Ptr<Texture> Blank;

  /**
  Construct an empty texture.
  See @link#load to build the texture.
  */
  Texture();

  /**
  Construct a texture from an image path.
  @param pathToImage Path to image
  */
  Texture(std::string pathToImage);
  ~Texture();

  /**
  Build the texture from an image.
  @param pathToImage Path to image
  */
  bool load(std::string pathToImage);

  /**
  Set the texture filters.

  @param type   Filter type
  @param value  Filter value
  */
  void setFilter(FilterType type, FilterValue value);

  /**
  Get the texture ID.
  @return Texture ID
  */
  GLuint getID();

  //////////////////////////

  /**
  Create a color buffer (used in framebuffers).

  @param width  Texture width
  @param height Texture height
  @return Texture (Ptr)
  */
  static Ptr<Texture> createColorBuffer(unsigned int width, unsigned int height);

  /**
  Use the current texture for drawing.
  @param texture Texture (Ptr)
  */
  static void use(Ptr<Texture> texture);

  /**
  Use the current font atlas for drawing.
  @param font Font (Ptr)
  */
  static void use(Ptr<Font> font);

  /**
  Clear the current texture for drawing.
  */
  static void disable();

  friend class Application;

private:
  GLuint _id;
  unsigned int _width;
  unsigned int _height;

  /**
  Invert the texture pixels after they have been loaded.
  If you don't, the texture is in the wrong direction.

  @param src Source surface
  @return Inverted surface
  */
  SDL_Surface* invertPixels(SDL_Surface* src) const;

  //////////////////////

  /**
  Used to create the Texture::Blank texture.
  */
  static void generateBlankTexture();
};

} /* hx3d */

#endif
