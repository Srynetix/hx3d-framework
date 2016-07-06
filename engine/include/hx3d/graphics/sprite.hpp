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

#pragma once

#include "hx3d/graphics/mesh.hpp"

namespace hx3d {
namespace graphics {

class Framebuffer;
class TextureRegion;
class Texture;

/**
@brief 2D texture manipulation.

<i>Example code</i>
@code
// Inside a create function...

Sprite sprite;

// Load the texture "my_texture"
sprite.setTexture(Core::Assets()->get<Texture>("my_texture"));

// Set the sprite coordinate to (5, 5)
sprite.transform.position.x = 5;
sprite.transform.position.y = 5;

[...]

// Inside a render function...

Framebuffer::clear(Color::Black);
batch.begin();

// Draw the sprite
batch.draw(sprite);

batch.end();
@endcode

*/
class Sprite: public Mesh {
  HX3D_PTR_REF(Sprite)

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
  void setTexture(const Pointer<Texture>& texture);

  /**
  @brief Set the sprite texture from a framebuffer color buffer.

  @param buffer Framebuffer
  */
  void setTexture(const Pointer<Framebuffer>& buffer);

  /**
  @brief Set the sprite texture from a texture region.

  @param region TextureRegion
  */
  void setTexture(const Pointer<TextureRegion>& region);

  /**
  @brief Get the sprite texture.

  @return Texture (Ptr)
  */
  Pointer<Texture> getTexture();

  /**
  @brief Scale the texture coordinates following the texture size.
  */
  void scaleTexture();

  virtual void draw(const Pointer<Shader>& shader) override;

private:
  /// @brief Current texture
  Pointer<Texture> _texture;
};

} /* graphics */
} /* hx3d */
