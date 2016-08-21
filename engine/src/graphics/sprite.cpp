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

#include "hx3d/graphics/sprite.hpp"

#include "hx3d/graphics/geometries/sprite_geometry.hpp"
#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/texture_region.hpp"
#include "hx3d/graphics/framebuffer.hpp"

namespace hx3d {
namespace graphics {

Sprite::Sprite():
Mesh() {
  _geometry = Make<SpriteGeometry>();
  _geometry->setFaceCulling(Culling::Back);

  setTint(Color::White);

  this->setTexture(Texture::Blank);
}

void Sprite::setTexture(const Pointer<Texture>& texture) {
  _texture = texture;

  this->setSize(_texture->getWidth(), _texture->getHeight());

  /* Set the correct texture coordinates, in case of previous framebuffer. */
  Pointer<SpriteGeometry> spriteGeo = std::dynamic_pointer_cast<SpriteGeometry>(_geometry);
  spriteGeo->activateTextureMode();

  _geometry->uploadAll();
}

void Sprite::setTexture(const Pointer<Framebuffer>& buffer) {
  _texture = buffer->getColorBuffer();

  this->setSize(_texture->getWidth(), _texture->getHeight());

  /* Reverse the framebuffer ! */
  Pointer<SpriteGeometry> spriteGeo = std::dynamic_pointer_cast<SpriteGeometry>(_geometry);
  spriteGeo->activateFramebufferMode();

  _geometry->uploadAll();
}

void Sprite::setTexture(const Pointer<TextureRegion>& region) {
  _texture = region->getTexture();

  this->setSize(region->getMaxX() - region->getMinX(),
                region->getMaxY() - region->getMinY());

  Pointer<SpriteGeometry> spriteGeo = std::dynamic_pointer_cast<SpriteGeometry>(_geometry);
  spriteGeo->setFromRegion(region);

  _geometry->uploadAll();
}

Pointer<Texture> Sprite::getTexture() {
  return _texture;
}

void Sprite::scaleTexture() {
  float ratioW = this->getSize().x / _texture->getWidth();
  float ratioH = this->getSize().y / _texture->getHeight();

  auto& uv = _geometry->getAttributeBuffer("Texture").getVector();
  for (unsigned int i = 0; i < uv.size(); i+=2) {
    if (uv[i] != 0)
      uv[i] = ratioW;

    if (uv[i+1] != 0)
      uv[i+1] = ratioH;
  }

  _geometry->uploadAll();
}

void Sprite::draw(const Pointer<Shader>& shader) {
  Texture::use(_texture);
  Mesh::draw(shader);
  Texture::disable();
}

} /* graphics */
} /* hx3d */
