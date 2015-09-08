/*
    Waveform display.
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

#include "hx3d/audio/display/waveform.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace audio {

Waveform::Waveform(): Waveform(50) {}
Waveform::Waveform(int refreshDelay): _refreshDelay(refreshDelay) {
  _initialized = false;
}

Waveform::~Waveform() {}

void Waveform::create(unsigned int width, unsigned int height) {
  _image.create(width, height);
  _image.buildTexture();
  _timer.initialize(_refreshDelay);

  _initialized = true;
}

void Waveform::setRefreshDelay(float refreshDelay) {
  _refreshDelay = refreshDelay;
  _timer.initialize(refreshDelay);
}

void Waveform::update(Sint16* stream, int length) {

  if (!_initialized)
    return;

  int w = _image.getWidth();
  int h = _image.getHeight();

  if (_timer.isEnded()) {

    _image.setRect(0, 0, w, h, Color::Black);
    drawBox();

    if (length > 0) {
      int step = length / w;

      for (int i = 1; i < w - 1; ++i) {
        int amp = stream[i * step];
        if (amp == 0)
          continue;

        float normalized_amp = (1.f/32767.f) * amp;
        normalized_amp = 0.5f + normalized_amp / 2;

        int y_pos = 0;
        int bar_h = 0;

        y_pos = (h/2.f) - (normalized_amp * (h/2.f));
        bar_h = (normalized_amp * (h/2.f)) * 2;

        _image.setRect(i, y_pos, 1, bar_h, Color::Red);
      }
    }

    _image.updateTextureZone(0, 0, w, h);
    _timer.reset();
  }
}

Ptr<Texture> Waveform::getTexture() {
  return _image.getTexture();
}

///////////////////////////////////////

void Waveform::drawBox() {
  _image.setRect(0, 0, _image.getWidth(), 1, Color::White);
  _image.setRect(0, 0, 1, _image.getHeight(), Color::White);
  _image.setRect(_image.getWidth() - 1, 0, 1, _image.getHeight(), Color::White);
  _image.setRect(0, _image.getHeight() - 1, _image.getWidth(), 1, Color::White);
}

} /* audio */
} /* hx3d */
