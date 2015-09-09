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

#include "hx3d/math/number_utils.hpp"

namespace hx3d {
namespace audio {

Spectrum::Spectrum(unsigned int minFreq, unsigned int maxFreq, unsigned int barsCount):
  Spectrum(minFreq, maxFreq, barsCount, 50)
  {}

Spectrum::Spectrum(unsigned int minFreq, unsigned int maxFreq, unsigned int barsCount, int refreshDelay):
  Display(refreshDelay),
  _minFreq(minFreq),
  _maxFreq(maxFreq),
  _barsCount(barsCount)
  {}

Spectrum::~Spectrum() {}

void Spectrum::onInitialization() {
  unsigned int resolutionX = _image.getWidth();

  _rawValues = new Complex[resolutionX];
  for (unsigned int i = 0; i < resolutionX; ++i) {
    _rawValues[i] = Complex(0, 0);
  }

  _fftValues.resize(resolutionX / 2);
  for (unsigned int i = 0; i < _fftValues.size(); ++i) {
    _fftValues[i] = 0.f;
  }

  _barsValues.resize(_barsCount);
  for (unsigned int i = 0; i < _barsValues.size(); ++i) {
    _barsValues[i] = 0.f;
  }

  _normalizedBarValues.resize(_barsCount);
  for (unsigned int i = 0; i < _normalizedBarValues.size(); ++i) {
    _normalizedBarValues[i] = 0.f;
  }
}

void Spectrum::update(Sint16* stream, int length) {

  if (!_initialized || length == 0)
    return;

  int w = _image.getWidth();
  int h = _image.getHeight();
  int step = length / w;

  if (_timer.isEnded()) {

    /* FFT */

    for (int i = 0; i < w; ++i) {
      float norm_amp = stream[i * step] * (1.f/32767.f);
      _rawValues[i] = Complex(norm_amp, 0);
    }

    std::valarray<Complex> fftArray(_rawValues, w);
    audio::FFT::fft(fftArray);

    for (int i = 0; i < w/2; ++i) {
      _fftValues[i] = std::log10(std::abs(fftArray[i])) * 20;
    }

    float octaves = calculateOctave(_minFreq, _maxFreq, _barsCount);
    unsigned int currentFreq = _minFreq;
    for (unsigned int i = 0; i < _barsCount; ++i) {

      int low = lowerLimitSample(currentFreq, octaves, w/2);
      int hi = upperLimitSample(currentFreq, octaves, w/2);

      if (currentFreq > Core::AudioDevice()->getFrequencyRate() || hi > w/2)
        break;

      // Log.Info("C: %d [L: %d / H: %d]", currentFreq, low, hi);

      _barsValues[i] = averageFreq(_fftValues, low, hi);
      currentFreq = nextCenterFreq(currentFreq, octaves);
    }

    /* END FFT */

    _image.setRect(0, 0, w, h, Color::Black);
    drawBorders();

    int bar_size = w / (float)_barsCount;
    for (unsigned int i = 0; i < _barsCount; ++i) {

      float scale_val = std::max(0.f, _barsValues[i]);
      float norm_val = scale_val / 40.f;

      _normalizedBarValues[i] = norm_val;

      Color color = Color::interp(Color(255, 64, 0), Color::Red, norm_val);

      // Values
      // Log.Info("Bar %d: %f", i, val);

      int y = h - norm_val * h;
      _image.setRect(i*bar_size, y + 1, bar_size, h - y - 2, color);
    }

    _image.updateTextureZone(0, 0, w, h);
    _timer.reset();
  }
}

std::vector<float>& Spectrum::getNormalizedBarValues() {
  return _normalizedBarValues;
}

float Spectrum::getNormalizedBarValue(unsigned int bar) {
  if (bar > _barsCount) {
    Log.Info("Spectrum: bar `%d` off-limits (max: %d)", bar, _barsCount);
    return 0.f;
  }

  return _normalizedBarValues[bar];
}

unsigned int Spectrum::getBarCount() {
  return _barsCount;
}

////////////////////////////////

int Spectrum::nextCenterFreq(int centerFreq, float octaves) {
  return centerFreq * std::pow(2, 1.f / octaves);
}
int Spectrum::prevCenterFreq(int centerFreq, float octaves) {
  return centerFreq / std::pow(2, 1.f / octaves);
}

int Spectrum::lowerLimit(int centerFreq, float octaves) {
  return centerFreq / std::pow(2, 1.f / (2.f * octaves));
}
int Spectrum::upperLimit(int centerFreq, float octaves) {
  return centerFreq * std::pow(2, 1.f / (2.f * octaves));
}

int Spectrum::lowerLimitSample(int centerFreq, float octaves, int samplesLength) {
  return lowerLimit(centerFreq, octaves) / (Core::AudioDevice()->getFrequencyRate() / samplesLength);
}
int Spectrum::upperLimitSample(int centerFreq, float octaves, int samplesLength) {
  return upperLimit(centerFreq, octaves) / (Core::AudioDevice()->getFrequencyRate() / samplesLength);
}

float Spectrum::averageFreq(std::vector<float>& values, int low, int hi) {
  if (low == hi)
    return 0;

  float sum = 0;
  for (int i = low; i < hi; ++i) {
    float val = values[i];
    sum += val;
  }

  return sum/(hi-low);
}

float Spectrum::calculateOctave(unsigned int lowFreq, unsigned int hiFreq, unsigned int bars) {
  return (bars - 1) / (math::log2(hiFreq / (float)lowFreq));
}

} /* audio */
} /* hx3d */
