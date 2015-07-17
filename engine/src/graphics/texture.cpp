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

#include "hx3d/graphics/texture.hpp"

#include <SDL2/SDL_image.h>

#include "hx3d/graphics/font.hpp"

#include "hx3d/utils/file.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {

  Ptr<Texture> Texture::Blank(nullptr);

  Texture::Texture(std::string pathToImage): Texture() {
    load(pathToImage);
  }

  Texture::Texture():
    _id(0),
    _width(0),
    _height(0)
  {}

  Texture::~Texture()
  {
    if (glIsTexture(_id)) {
      glDeleteTextures(1, &_id);
    }
  }

  bool Texture::load(std::string pathToImage) {
    SDL_Surface* image = nullptr;

    Ptr<File> file = File::loadBinaryFile(pathToImage);

    SDL_RWops* imageOps = SDL_RWFromConstMem(file->data, file->size);
    image = IMG_Load_RW(imageOps, 1);

    if (image == nullptr) {
      Log.Error("Invalid image: %s", pathToImage.c_str());
      return false;
    }

    SDL_Surface* formatted = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(image);

    SDL_Surface* inverted = invertPixels(formatted);
    SDL_FreeSurface(formatted);

    _width = inverted->w;
    _height = inverted->h;

    glGenTextures(1, &_id);

    glBindTexture(GL_TEXTURE_2D, _id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, inverted->pixels);

    // Base filter = Nearest
    setFilter(FilterType::Min, FilterValue::Nearest);
    setFilter(FilterType::Max, FilterValue::Nearest);

    glBindTexture(GL_TEXTURE_2D, 0);

    Log.Info("Texture %s loaded.", pathToImage.c_str());

    SDL_FreeSurface(inverted);
    return true;
  }

  void Texture::setFilter(FilterType type, FilterValue value) {
    GLenum filterType;
    GLenum filterValue;

    if (type == FilterType::Min)
      filterType = GL_TEXTURE_MIN_FILTER;
    else
      filterType = GL_TEXTURE_MAG_FILTER;

    if (value == FilterValue::Linear)
      filterValue = GL_LINEAR;
    else
      filterValue = GL_NEAREST;

    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, filterType, filterValue);

    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void Texture::use(Ptr<Texture> texture) {
    glBindTexture(GL_TEXTURE_2D, texture->_id);
  }

  void Texture::use(Ptr<Font> font) {
    glBindTexture(GL_TEXTURE_2D, font->atlas->id);
  }

  void Texture::disable() {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  Ptr<Texture> Texture::createColorBuffer(unsigned int width, unsigned int height) {
    Ptr<Texture> texture(Make<Texture>());

    texture->_width = width;
    texture->_height = height;

    glGenTextures(1, &texture->_id);
    glBindTexture(GL_TEXTURE_2D, texture->_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->_width, texture->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    // Base filter = Nearest
    texture->setFilter(FilterType::Min, FilterValue::Nearest);
    texture->setFilter(FilterType::Max, FilterValue::Nearest);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
  }

  GLuint Texture::getID() {
    return _id;
  }

  SDL_Surface* Texture::invertPixels(SDL_Surface* src) const {
    SDL_Surface* inverted = SDL_CreateRGBSurface(0, src->w, src->h, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask);

    unsigned char* srcPixels = (unsigned char*) src->pixels;
    unsigned char* invertedPixels = (unsigned char*) inverted->pixels;

    for (int i = 0; i < src->h; ++i) {
      for (int j = 0; j < src->w * 4; ++j) {
        invertedPixels[(src->w * 4 * (src->h - 1 - i)) + j] = srcPixels[(src->w * 4 * i) + j];
      }
    }

    return inverted;
  }

  void Texture::generateBlankTexture() {
    Ptr<Texture> texture(Make<Texture>());

    texture->_width = 1;
    texture->_height = 1;

    glGenTextures(1, &texture->_id);
    glBindTexture(GL_TEXTURE_2D, texture->_id);

    int pixels[] = {
      -1, -1, -1, 0,
    };

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->_width, texture->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // Base filter = Nearest
    texture->setFilter(FilterType::Min, FilterValue::Nearest);
    texture->setFilter(FilterType::Max, FilterValue::Nearest);

    glBindTexture(GL_TEXTURE_2D, 0);
    Blank = texture;
  }

} /* hx3d */
