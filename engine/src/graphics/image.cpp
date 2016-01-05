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

#include "hx3d/graphics/image.hpp"
#include "hx3d/graphics/texture.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace graphics {

Image::Image(): _width(0), _height(0), _buffer(nullptr), _texture(nullptr) {}

Image::Image(unsigned int width, unsigned int height) {
  create(width, height);
}

Image::~Image() {}

void Image::create(unsigned int width, unsigned int height) {
  _width = width;
  _height = height;

  _buffer = new unsigned char[width * height * 4] {};
}

void Image::set(unsigned int x, unsigned int y, Color color) {
  unsigned int pos = x * 4 + (y * _width * 4);
  _buffer[pos] = color.r;
  _buffer[pos + 1] = color.g;
  _buffer[pos + 2] = color.b;
  _buffer[pos + 3] = color.a;
}

void Image::setRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Color color) {

  if (x + w > _width) {
    Log.Error("Image: can't rect. width is too high.");
    return;
  } else if (y + h > _height) {
    Log.Error("Image: can't rect. height is too high.");
    return;
  }

  for (auto j = y; j < y + h; ++j) {
    for (auto i = x; i < x + w; ++i) {
      set(i, j, color);
    }
  }
}

Color Image::get(unsigned int x, unsigned int y) {
  unsigned int pos = x * 4 + (y * _width * 4);
  return Color(_buffer[pos], _buffer[pos + 1], _buffer[pos + 2], _buffer[pos + 3]);
}

Ptr<Texture> Image::getTexture() {
  if (!_texture)
    Log.Error("Image: attempt to access a non-created texture.");

  return _texture;
}

void Image::buildTexture() {
  _texture = Make<Texture>(*this);
}

void Image::updateTextureZone(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
  if (!_texture) {
    Log.Error("Image: attempt to update a non-created texture.");
    return;
  }

  Uint8* subBuffer = new Uint8[w * h * 4];
  for (unsigned int j = y, count = 0; j < y + h; ++j) {
    for (unsigned int i = x; i < x + w; ++i, count += 4) {

      Color color = get(i, j);
      subBuffer[count] = color.r;
      subBuffer[count+1] = color.g;
      subBuffer[count+2] = color.b;
      subBuffer[count+3] = color.a;
    }
  }

  _texture->updateZone(x, y, w, h, subBuffer);

  delete[] subBuffer;
}

unsigned int Image::getWidth() {
  return _width;
}

unsigned int Image::getHeight() {
  return _height;
}

} /* graphics */
} /* hx3d */
