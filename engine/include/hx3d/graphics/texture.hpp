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

#include "hx3d/graphics/font.hpp"
#include "hx3d/graphics/image.hpp"
#include "hx3d/graphics/gl.hpp"

#include <string>

namespace hx3d {
namespace graphics {

/**
@brief 2D/3D texture management.
*/
class Texture: public Resource {

public:
  /**
  @brief Filtering type
  */
  enum class FilterType {

    /// @brief Min. filter
    Min,
    /// @brief Max. filter
    Max,

    /// @brief S wrapping filter
    WrapX,
    /// @brief T wrapping filter
    WrapY
  };

  /**
  @brief Filtering value
  */
  enum class FilterValue {

    /* Min and Max */

    /// @brief Linear filter
    Linear,
    /// @brief Nearest filter
    Nearest,

    /* Min only */

    /// @brief Linear Mipmap Linear
    LinearMipmapLinear,
    /// @brief Nearest Mipmap Linear
    NearestMipmapLinear,
    /// @brief Linear Mipmap Nearest
    LinearMipmapNearest,
    /// @brief Nearest Mipmap Nearest
    NearestMipmapNearest,

    /* WrapX and WrapY */

    /// @brief Clamp texture to edges
    ClampToEdge,
    /// @brief Repeat mirrored
    MirroredRepeat,
    /// @brief Repeat
    Repeat
  };

  /// @brief Default blank texture
  static Ptr<Texture> Blank;

  /**
  @brief Construct an empty texture.
  See @link load @endlink to build the texture.
  */
  Texture();

  /**
  @brief Construct a texture from an image path.

  @param pathToImage Path to image
  */
  Texture(std::string pathToImage);

  /**
  @brief Construct a texture from an memory image.

  @param image Image
  */
  Texture(Image& image);
  ~Texture();

  /**
  @brief Build the texture from an image.

  @param pathToImage Path to image

  @return OK/Error
  */
  bool load(std::string pathToImage);

  /**
  @brief Set the texture filters.

  @param type   Filter type
  @param value  Filter value
  */
  void setFilter(FilterType type, FilterValue value);

  /**
  @brief Update a zone in the texture.

  @param x    X coordinate
  @param y    Y coordinate
  @param w    Width
  @param h    Height
  @param data Data
  */
  void updateZone(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Uint8* data);

  /**
  @brief Get the texture width.

  @return Width
  */
  unsigned int getWidth();

  /**
  @brief Get the texture height.

  @return Height
  */
  unsigned int getHeight();

  /**
  @brief Get the texture ID.

  @return Texture ID
  */
  GLuint getID();

  //////////////////////////

  /**
  @brief Create a color buffer (used in framebuffers).

  @param width  Texture width
  @param height Texture height

  @return Texture (Ptr)
  */
  static Ptr<Texture> createColorBuffer(unsigned int width, unsigned int height);

  /**
  @brief Use the current texture for drawing.

  @param texture Texture (Ptr)
  */
  static void use(Ptr<Texture> texture);

  /**
  @brief Use the current font atlas for drawing.

  @param font           Font (Ptr)
  @param characterSize  Character size
  */
  static void use(Ptr<Font> font, int characterSize);

  /**
  @brief Clear the current texture for drawing.
  */
  static void disable();

  /**
  @brief Used to create the Texture::Blank texture.
  */
  static void generateBlankTexture();

  friend class Application;

private:
  /// @brief Texture ID
  GLuint _id;
  /// @brief Width
  unsigned int _width;
  /// @brief Height
  unsigned int _height;

  //////////////////////
};

} /* graphics */
} /* hx3d */

#endif
