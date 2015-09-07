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

  Texture::Texture(Image& image): Texture() {
    _width = image._width;
    _height = image._height;

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image._buffer);

    // Base filter = Nearest
    setFilter(FilterType::Min, FilterValue::Nearest);
    setFilter(FilterType::Max, FilterValue::Nearest);

    glBindTexture(GL_TEXTURE_2D, 0);
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

    _width = formatted->w;
    _height = formatted->h;

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, formatted->pixels);

    // Base filter = Nearest
    setFilter(FilterType::Min, FilterValue::Nearest);
    setFilter(FilterType::Max, FilterValue::Nearest);

    glBindTexture(GL_TEXTURE_2D, 0);

    Log.Info("Texture %s loaded.", pathToImage.c_str());

    SDL_FreeSurface(formatted);
    return true;
  }

  void Texture::setFilter(FilterType type, FilterValue value) {
    GLenum filterType;
    GLenum filterValue;

    filterType =
      type == FilterType::Min ? GL_TEXTURE_MIN_FILTER :
      type == FilterType::Max ? GL_TEXTURE_MAG_FILTER :

      type == FilterType::WrapX ? GL_TEXTURE_WRAP_S :
      type == FilterType::WrapY ? GL_TEXTURE_WRAP_S : GL_INVALID_ENUM;

    filterValue =
      value == FilterValue::Linear ? GL_LINEAR :
      value == FilterValue::Nearest ? GL_NEAREST :

      value == FilterValue::LinearMipmapLinear ? GL_LINEAR_MIPMAP_LINEAR :
      value == FilterValue::NearestMipmapLinear ? GL_NEAREST_MIPMAP_LINEAR :
      value == FilterValue::LinearMipmapNearest ? GL_LINEAR_MIPMAP_NEAREST :
      value == FilterValue::NearestMipmapNearest ? GL_NEAREST_MIPMAP_NEAREST :

      value == FilterValue::ClampToEdge ? GL_CLAMP_TO_EDGE :
      value == FilterValue::MirroredRepeat ? GL_MIRRORED_REPEAT :
      value == FilterValue::Repeat ? GL_REPEAT : GL_INVALID_ENUM;

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

  unsigned int Texture::getWidth() {
    return _width;
  }

  unsigned int Texture::getHeight() {
    return _height;
  }

  void Texture::updateZone(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Uint8* data) {
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
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
