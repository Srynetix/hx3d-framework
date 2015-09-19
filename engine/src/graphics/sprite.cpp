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

namespace hx3d {

Sprite::Sprite():
  Sprite(Ptr<Texture>(nullptr)) {}

Sprite::Sprite(Ptr<Texture> texture):
  Mesh(), _texture(texture) {

    setAttribute("Position", std::vector<float> {
      -0.5f, 0.5f, 0.f,
      0.5, 0.5f, 0.f,
      0.5f, -0.5f, 0.f,
      -0.5f, -0.5f, 0.f
    });

    setIndices(std::vector<GLushort> {
      0, 2, 1,
      0, 3, 2
    });

    setAttribute("Color", std::vector<float> {
      1, 1, 1, 1,
      1, 1, 1, 1,
      1, 1, 1, 1,
      1, 1, 1, 1
    });

    setAttribute("Texture", std::vector<float> {
      0, 0,
      1, 0,
      1, 1,
      0, 1
    });

    uploadAll();

    if (_texture) {
      transform.size.x = _texture->getWidth();
      transform.size.y = _texture->getHeight();
    }

    setTint(Color::White);
  }

Sprite::Sprite(Framebuffer& buffer):
  Sprite(buffer.getColorBuffer()) {}

void Sprite::setTexture(Ptr<Texture> texture) {
  _texture = texture;

  transform.size.x = _texture->getWidth();
  transform.size.y = _texture->getHeight();

  /* Set the correct texture coordinates, in case of previous framebuffer. */

  setAttribute("Texture", std::vector<float> {
    0, 0,
    1, 0,
    1, 1,
    0, 1
  });

  uploadAll();
}

void Sprite::setTexture(Framebuffer& buffer) {
  _texture = buffer.getColorBuffer();

  transform.size.x = _texture->getWidth();
  transform.size.y = _texture->getHeight();

  /* Reverse the framebuffer ! */

  setAttribute("Texture", std::vector<float> {
    1, 0,
    0, 0,
    0, 1,
    1, 1
  });

  uploadAll();
}

Ptr<Texture> Sprite::getTexture() {
  return _texture;
}

void Sprite::scaleTexture() {
  float ratioW = transform.size.x / _texture->getWidth();
  float ratioH = transform.size.y / _texture->getHeight();

  auto& uv = getAttribute("Texture").getVector();
  for (unsigned int i = 0; i < uv.size(); i+=2) {
    if (uv[i] != 0)
      uv[i] = ratioW;

    if (uv[i+1] != 0)
      uv[i+1] = ratioH;
  }

  uploadAll();
}

void Sprite::draw(Ptr<Shader> shader) {
  Texture::use(_texture);

  Mesh::draw(shader);
}

} /* hx3d */
