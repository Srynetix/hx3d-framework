/*
    Sprite.
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

#ifndef HX3D_GRAPHICS_SPRITE
#define HX3D_GRAPHICS_SPRITE

#include "hx3d/graphics/mesh.hpp"
#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/framebuffer.hpp"
#include "hx3d/graphics/texture_region.hpp"

namespace hx3d {
namespace graphics {

/**
@brief 2D texture manipulation.
*/
class Sprite: public Mesh {

public:

  /**
  @brief Create a sprite without texture.

  You must set it after with @link setTexture @endlink.
  */
  Sprite();

  /**
  @brief Set the sprite texture.

  @param texture Texture (Ptr)
  */
  void setTexture(const Ptr<Texture>& texture);

  /**
  @brief Set the sprite texture from a framebuffer color buffer.

  @param buffer Framebuffer
  */
  void setTexture(Framebuffer& buffer);

  /**
  @brief Set the sprite texture from a texture region.

  @param region TextureRegion
  */
  void setTexture(TextureRegion& region);

  /**
  @brief Get the sprite texture.

  @return Texture (Ptr)
  */
  Ptr<Texture> getTexture();

  /**
  @brief Scale the texture coordinates following the texture size.
  */
  void scaleTexture();

  virtual void draw(Ptr<Shader> shader) override;

private:
  /// @brief Current texture
  Ptr<Texture> _texture;
};

} /* graphics */
} /* hx3d */

#endif
