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
#include "hx3d/math/interpolation.hpp"

namespace hx3d {
namespace audio {

Spectrum::Spectrum(const unsigned int minFreq, const unsigned int maxFreq, const unsigned int barCount):
  Spectrum(minFreq, maxFreq, barCount, 50)
  {}

Spectrum::Spectrum(const unsigned int minFreq, const unsigned int maxFreq, const unsigned int barCount, const int refreshDelay):
  Display(refreshDelay),
  _minFreq(minFreq),
  _maxFreq(maxFreq),
  _barCount(barCount)
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

  _barValues.resize(_barCount);
  for (unsigned int i = 0; i < _barValues.size(); ++i) {
    _barValues[i] = 0.f;
  }

  _normalizedBarValues.resize(_barCount);
  for (unsigned int i = 0; i < _normalizedBarValues.size(); ++i) {
    _normalizedBarValues[i] = 0.f;
  }

  _barFrequencies.resize(_barCount);
  for (unsigned int i = 0; i < _barFrequencies.size(); ++i) {
    _barFrequencies[i] = 0;
  }
}

void Spectrum::update(const short int* stream, const int length, const float delta) {

  if (!_initialized || length == 0)
    return;

  int w = _image.getWidth();
  int h = _image.getHeight();
  int step = length / w;

  if (_timer.hasEnded()) {

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

    float octaves = calculateOctave(_minFreq, _maxFreq, _barCount);
    unsigned int currentFreq = _minFreq;
    for (unsigned int i = 0; i < _barCount; ++i) {

      int low = lowerLimitSample(currentFreq, octaves, w/2);
      int hi = upperLimitSample(currentFreq, octaves, w/2);

      if (currentFreq > Core::Audio()->getFrequencyRate() || hi > w/2)
        break;

      // Log.Info("C: %d [L: %d / H: %d]", currentFreq, low, hi);

      _barFrequencies[i] = currentFreq;

      _barValues[i] = averageFreq(_fftValues, low, hi);
      currentFreq = nextCenterFreq(currentFreq, octaves);
    }

    /* END FFT */

    _image.setRect(0, 0, w, h, Color::Black);
    drawBorders();

    int bar_size = w / (float)_barCount;
    for (unsigned int i = 0; i < _barCount; ++i) {

      float scale_val = std::max(0.f, _barValues[i]);
      float norm_val = scale_val / 30.f;

      _normalizedBarValues[i] = norm_val;

      Color color = math::interpolate(Color(255, 64, 0), Color::Red, norm_val, math::Interpolation::Linear);

      // Values
      // Log.Info("Bar %d: %f", i, val);

      int y = h - norm_val * h;
      _image.setRect(i*bar_size, y + 1, bar_size, h - y - 2, color);
    }

    _image.updateTextureZone(0, 0, w, h);
    _timer.reset();
  }

  _timer.update(delta);
}

float Spectrum::getNormalizedFrequencyAmplitude(const unsigned int frequency, const unsigned int range) {
  unsigned int maxFrequency = _barFrequencies[_barCount - 1];

  if (frequency > maxFrequency) {
    Log.Info("Spectrum: frequency `%d` off-limits (max: %d)", frequency, maxFrequency);
    return 0.f;
  }

  unsigned int lowFreq = frequency - range;
  unsigned int hiFreq = frequency + range;
  unsigned int lowBar = 0;
  unsigned int hiBar = _barCount;

  for (unsigned int i = 0; i < _barCount; ++i) {
    unsigned int currentFreq = _barFrequencies[i];
    if (lowFreq >= currentFreq) {
      lowBar = i;
    }

    if (hiFreq >= currentFreq) {
      hiBar = i;
    }

    Log.Info("Freq[%d]: %d", i, currentFreq);
  }

  Log.Info("Freq: %d range %d [Min: %d / Max: %d] [I: %d / %d]", frequency, range, lowFreq, hiFreq, lowBar, hiBar);

  return averageFreq(_normalizedBarValues, lowBar, hiBar);
}

unsigned int Spectrum::getBarCount() {
  return _barCount;
}

////////////////////////////////

int Spectrum::nextCenterFreq(const int centerFreq, const float octaves) {
  return centerFreq * std::pow(2, 1.f / octaves);
}
int Spectrum::prevCenterFreq(const int centerFreq, const float octaves) {
  return centerFreq / std::pow(2, 1.f / octaves);
}

int Spectrum::lowerLimit(const int centerFreq, const float octaves) {
  return centerFreq / std::pow(2, 1.f / (2.f * octaves));
}
int Spectrum::upperLimit(const int centerFreq, const float octaves) {
  return centerFreq * std::pow(2, 1.f / (2.f * octaves));
}

int Spectrum::lowerLimitSample(const int centerFreq, const float octaves, const int samplesLength) {
  return lowerLimit(centerFreq, octaves) / (Core::Audio()->getFrequencyRate() / samplesLength);
}
int Spectrum::upperLimitSample(const int centerFreq, const float octaves, const int samplesLength) {
  return upperLimit(centerFreq, octaves) / (Core::Audio()->getFrequencyRate() / samplesLength);
}

float Spectrum::averageFreq(const std::vector<float>& values, const int low, const int hi) {
  if (low == hi)
    return 0;

  float sum = 0;
  int count = 1;

  for (int i = low; i < hi; ++i) {
    const float val = values[i];
    if (val != 0.f) {
      sum += val;
      ++count;
    }
  }

  return sum/count;
}

float Spectrum::calculateOctave(const unsigned int lowFreq, const unsigned int hiFreq, const unsigned int bars) {
  return (bars - 1) / (math::log2(hiFreq / (float)lowFreq));
}

} /* audio */
} /* hx3d */
