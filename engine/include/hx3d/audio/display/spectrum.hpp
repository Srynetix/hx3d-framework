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

#ifndef HX3D_AUDIO_DISPLAY_SPECTRUM
#define HX3D_AUDIO_DISPLAY_SPECTRUM

#include "hx3d/audio/display.hpp"
#include "hx3d/math/constants.hpp"

namespace hx3d {
namespace audio {

class Spectrum: public Display {
public:
  /**
  Create an empty spectrum with a refresh delay of 50.
  See @link#create to construct the texture.

  @param minFreq    Min. frequency
  @param maxFreq    Max. frequency
  @param barsCount  Bars count
  */
  Spectrum(unsigned int minFreq, unsigned int maxFreq, unsigned int barsCount);

  /**
  Create an empty spectrum with a custom refresh delay.
  See @link#create to construct the texture.

  @param minFreq      Min. frequency
  @param maxFreq      Max. frequency
  @param barsCount    Bars count
  @param refreshDelay Refresh delay
  */
  Spectrum(unsigned int minFreq, unsigned int maxFreq, unsigned int barsCount, int refreshDelay);
  ~Spectrum();

  virtual void update(Sint16* stream, int length) override;
  virtual void onInitialization() override;

  float getNormalizedBarValue(unsigned int bar);
  std::vector<float>& getNormalizedBarValues();

  unsigned int getBarCount();

private:
  unsigned int _minFreq;
  unsigned int _maxFreq;
  unsigned int _barsCount;

  Complex* _rawValues;
  std::vector<float> _fftValues;
  std::vector<float> _barsValues;
  std::vector<float> _normalizedBarValues;

  int nextCenterFreq(int centerFreq, float octaves);
  int prevCenterFreq(int centerFreq, float octaves);
  int lowerLimit(int centerFreq, float octaves);
  int lowerLimitSample(int centerFreq, float octaves, int samplesLength);
  int upperLimit(int centerFreq, float octaves);
  int upperLimitSample(int centerFreq, float octaves, int samplesLength);
  float averageFreq(std::vector<float>& values, int low, int hi);
  float calculateOctave(unsigned int lowFreq, unsigned int hiFreq, unsigned int bars);
};

} /* audio */
} /* hx3d */

#endif
