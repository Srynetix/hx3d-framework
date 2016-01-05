/*
    Audio effect display.
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

#include "hx3d/audio/display.hpp"

namespace hx3d {
namespace audio {

using ::hx3d::graphics::Color;

Display::Display(): Display(50) {}
Display::Display(const int refreshDelay): _refreshDelay(refreshDelay), _initialized(false) {}
Display::~Display() {}

void Display::initialize(const unsigned int width, const unsigned int height) {
  _image.create(width, height);
  _image.buildTexture();
  _timer.initialize(_refreshDelay);

  Sprite::setTexture(_image.getTexture());

  onInitialization();

  _initialized = true;
}

void Display::setRefreshDelay(const int refreshDelay) {
  _refreshDelay = refreshDelay;
  _timer.initialize(_refreshDelay);
}

void Display::onInitialization() {}

void Display::drawBorders() {
  _image.setRect(0, 0, _image.getWidth(), 1, Color::White);
  _image.setRect(0, 0, 1, _image.getHeight(), Color::White);
  _image.setRect(_image.getWidth() - 1, 0, 1, _image.getHeight(), Color::White);
  _image.setRect(0, _image.getHeight() - 1, _image.getWidth(), 1, Color::White);
}

} /* audio */
} /* hx3d */
