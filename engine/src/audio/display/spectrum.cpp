/*
    Spectrum display.
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

#include "hx3d/audio/display/spectrum.hpp"
#include "hx3d/audio/fft.hpp"
#include "hx3d/audio/audio.hpp"

#include "hx3d/core/core.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace audio {

int nextCenterFreq(int centerFreq, float octaves) {
  return centerFreq * std::pow(2, 1.f / octaves);
}

int prevCenterFreq(int centerFreq, float octaves) {
  return centerFreq / std::pow(2, 1.f / octaves);
}

int lowerLimit(int centerFreq, float octaves) {
  return centerFreq / std::pow(2, 1.f / (2.f * octaves));
}
int upperLimit(int centerFreq, float octaves) {
  return centerFreq * std::pow(2, 1.f / (2.f * octaves));
}

int lowerLimitSample(int centerFreq, float octaves, int samplesLength) {
  return lowerLimit(centerFreq, octaves) / (Core::AudioDevice()->getFrequencyRate() / samplesLength);
}
int upperLimitSample(int centerFreq, float octaves, int samplesLength) {
  return upperLimit(centerFreq, octaves) / (Core::AudioDevice()->getFrequencyRate() / samplesLength);
}

float averageFreq(std::vector<float>& values, int low, int hi) {

  if (low == hi)
    return 0;

  float sum = 0;
  for (int i = low; i < hi; ++i) {
    float val = values[i];
    sum += val;
  }

  return sum/(hi-low);
}

Spectrum::Spectrum(): Spectrum(50) {}
Spectrum::Spectrum(int refreshDelay): _refreshDelay(refreshDelay) {
  _initialized = false;
}

Spectrum::~Spectrum() {}

void Spectrum::create(unsigned int width, unsigned int height) {
  _image.create(width, height);
  _image.buildTexture();
  _timer.initialize(_refreshDelay);

  _initialized = true;
}

void Spectrum::setRefreshDelay(float refreshDelay) {
  _refreshDelay = refreshDelay;
  _timer.initialize(refreshDelay);
}

void Spectrum::update(Sint16* stream, int length) {

  if (!_initialized || length == 0)
    return;

  int w = _image.getWidth();
  int h = _image.getHeight();
  int step = length / w;

  if (_timer.isEnded()) {

    /* FFT */

    Complex* data = new Complex[w];
    for (int i = 0; i < w; ++i) {

      float norm_amp = stream[i * step] * (1.f/32767.f);
      data[i] = Complex(norm_amp, 0);
    }

    std::valarray<Complex> tab(data, w);
    audio::FFT::fft(tab);

    std::vector<float> values;
    values.reserve(w/2);

    for (int i = 0; i < w/2; ++i) {
      Complex& c = tab[i];
      values[i] = std::log10(std::abs(c)) * 20;
    }

    delete[] data;

    /* END FFT */

    _image.setRect(0, 0, w, h, Color::Black);
    drawBox();

    unsigned int currentFreq = 200;
    float octaves = 3.5f;
    int bars = 24;

    std::vector<float> final_values;
    final_values.reserve(bars);
    for (int i = 0; i < bars; ++i) {
      final_values[i] = 0;
    }

    for (int i = 0; i < bars; ++i) {

      int low = lowerLimitSample(currentFreq, octaves, w/2);
      int hi = upperLimitSample(currentFreq, octaves, w/2);

      if (currentFreq > Core::AudioDevice()->getFrequencyRate() || hi > w/2)
        break;

      // Log.Info("C: %d [L: %d / H: %d]", currentFreq, low, hi);

      final_values[i] = averageFreq(values, low, hi);
      currentFreq = nextCenterFreq(currentFreq, octaves);
    }

    int bar_size = w / (float)bars;
    for (int i = 0; i < bars; ++i) {

      float val = final_values[i];
      float norm_val = std::max(0.f, val / 50.f);

      // Values
      // Log.Info("Bar %d: %f", i, val);

      int y = h - norm_val * h;
      _image.setRect(i*bar_size, y + 1, bar_size, h - y - 2, Color::Blue);
    }

    _image.updateTextureZone(0, 0, w, h);
    _timer.reset();
  }
}

Ptr<Texture> Spectrum::getTexture() {
  return _image.getTexture();
}

///////////////////////////////////////

void Spectrum::drawBox() {
  _image.setRect(0, 0, _image.getWidth(), 1, Color::White);
  _image.setRect(0, 0, 1, _image.getHeight(), Color::White);
  _image.setRect(_image.getWidth() - 1, 0, 1, _image.getHeight(), Color::White);
  _image.setRect(0, _image.getHeight() - 1, _image.getWidth(), 1, Color::White);
}

} /* audio */
} /* hx3d */
