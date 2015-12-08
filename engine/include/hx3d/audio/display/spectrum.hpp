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
  Spectrum(const unsigned int minFreq, const unsigned int maxFreq, const unsigned int barCount);

  /**
  Create an empty spectrum with a custom refresh delay.
  See @link#create to construct the texture.

  @param minFreq      Min. frequency
  @param maxFreq      Max. frequency
  @param barsCount    Bars count
  @param refreshDelay Refresh delay
  */
  Spectrum(const unsigned int minFreq, const unsigned int maxFreq, const unsigned int barCount, const int refreshDelay);
  ~Spectrum();

  virtual void update(const Sint16* stream, const int length, const float delta) override;
  virtual void onInitialization() override;

  /**
  Get the average normalized amplitude for a center frequency and a range.
  Use this to detect a "beat" into a frequency range.

  @param frequency  Center frequency
  @param range      Range
  @return Normalized amplitude
  */
  float getNormalizedFrequencyAmplitude(const unsigned int frequency, const unsigned int range);

  /*
  Get the bar count.

  @return Bar count
  */
  unsigned int getBarCount();

private:
  unsigned int _minFreq;
  unsigned int _maxFreq;
  unsigned int _barCount;

  Complex* _rawValues;
  std::vector<float> _fftValues;
  std::vector<float> _barValues;
  std::vector<float> _normalizedBarValues;
  std::vector<unsigned int> _barFrequencies;

  /**
  Get the center frequency for the next bar, using an octave value.

  @param centerFreq Current center frequency
  @param octaves    Octave value
  @return Next center frequency
  */
  int nextCenterFreq(const int centerFreq, const float octaves);

  /**
  Get the center frequency for the previous bar, using an octave value.

  @param centerFreq Current center frequency
  @param octaves    Octave value
  @return Previous center frequency
  */
  int prevCenterFreq(const int centerFreq, const float octaves);

  /**
  Get the lower frequency limit for the current bar, using an octave value.

  @param centerFreq Current center frequency
  @param octaves    Octave value
  @return Lower frequency limit
  */
  int lowerLimit(const int centerFreq, const float octaves);

  /**
  Get the lower frequency limit sample index for the current bar,
  e.g. the sample index into the stream, for an octave value and a
  sample length.

  @param centerFreq Current center frequency
  @param octaves    Octave value
  @return Lower frequency limit sample index
  */
  int lowerLimitSample(const int centerFreq, const float octaves, const int samplesLength);

  /**
  Get the upper frequency limit for the current bar, using an octave value.

  @param centerFreq Current center frequency
  @param octaves    Octave value
  @return Upper frequency limit
  */
  int upperLimit(const int centerFreq, const float octaves);

  /**
  Get the upper frequency limit sample index for the current bar,
  e.g. the sample index into the stream, for an octave value and a
  sample length.

  @param centerFreq Current center frequency
  @param octaves    Octave value
  @return Upper frequency limit sample index
  */
  int upperLimitSample(const int centerFreq, const float octaves, const int samplesLength);

  /**
  Calculate the average frequency between a low and hi index interval.

  @param values Bar values
  @param low    Low frequency index
  @param hi     High frequency index
  @return Average frequency
  */
  float averageFreq(const std::vector<float>& values, const int low, const int hi);

  /**
  Calculate the octave value, using a low frequency limit and a
  hi frequency limit, for a number of bars.

  @param lowFreq  Low frequency limit
  @param hiFreq   Hi frequency limit
  @param bars     Bar count
  @return Octave value
  */
  float calculateOctave(const unsigned int lowFreq, const unsigned int hiFreq, const unsigned int bars);
};

} /* audio */
} /* hx3d */

#endif
