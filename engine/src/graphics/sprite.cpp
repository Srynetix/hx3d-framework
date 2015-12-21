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

namespace hx3d {

Sprite::Sprite():
Mesh() {
  _geometry = Make<SpriteGeometry>();

  setTint(Color::White);
}

void Sprite::setTexture(const Ptr<Texture>& texture) {
  _texture = texture;

  transform.size.x = _texture->getWidth();
  transform.size.y = _texture->getHeight();

  /* Set the correct texture coordinates, in case of previous framebuffer. */
  Ptr<SpriteGeometry> spriteGeo = std::dynamic_pointer_cast<SpriteGeometry>(_geometry);
  spriteGeo->activateTextureMode();

  _geometry->uploadAll();
}

void Sprite::setTexture(Framebuffer& buffer) {
  _texture = buffer.getColorBuffer();

  transform.size.x = _texture->getWidth();
  transform.size.y = _texture->getHeight();

  /* Reverse the framebuffer ! */
  Ptr<SpriteGeometry> spriteGeo = std::dynamic_pointer_cast<SpriteGeometry>(_geometry);
  spriteGeo->activateFramebufferMode();

  _geometry->uploadAll();
}

void Sprite::setTexture(TextureRegion& region) {
  _texture = region.getTexture();

  transform.size.x = region.getMaxX() - region.getMinX();
  transform.size.y = region.getMaxY() - region.getMinY();

  Ptr<SpriteGeometry> spriteGeo = std::dynamic_pointer_cast<SpriteGeometry>(_geometry);
  spriteGeo->setFromRegion(region);

  _geometry->uploadAll();
}

Ptr<Texture> Sprite::getTexture() {
  return _texture;
}

void Sprite::scaleTexture() {
  float ratioW = transform.size.x / _texture->getWidth();
  float ratioH = transform.size.y / _texture->getHeight();

  auto& uv = _geometry->getAttribute("Texture").getVector();
  for (unsigned int i = 0; i < uv.size(); i+=2) {
    if (uv[i] != 0)
      uv[i] = ratioW;

    if (uv[i+1] != 0)
      uv[i+1] = ratioH;
  }

  _geometry->uploadAll();
}

void Sprite::draw(Ptr<Shader> shader) {
  Texture::use(_texture);
  Mesh::draw(shader);
}

} /* hx3d */
