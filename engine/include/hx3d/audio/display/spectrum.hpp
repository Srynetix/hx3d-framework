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

/**
@brief Audio spectrum displaying.

<i>Example code</i>
@code
// Inside a create function...

// Create a spectrum from 100Hz to 10KHz, with 10 bars
audio::Spectrum spectrum(100, 10000, 10);

spectrum.transform.position.x = 100;
spectrum.transform.position.y = 100;

[...]

// Inside an update function...

// Get a signed short stream (see audio::S16Converter)
short* stream = s16converter.getS16Stream();

// Update the spectrum
spectrum.update(stream, s16converter.getSampleSize(), delta);

// Look for an amplitude (for example 1KHz with a 500Hz range) -> between 0 and 1
float amp = spectrum.getNormalizedFrequencyAmplitude(1000, 500);

// > Do whatever you want with the amplitude ! (tempo measure ?)

[...]

// Inside a render function...

// Display the spectrum
batch.draw(spectrum);
@endcode
*/
class Spectrum: public Display {
public:
  /**
  @brief Create an empty spectrum with a refresh delay of 50.

  @see initialize to construct the texture.

  @param minFreq    Min. frequency
  @param maxFreq    Max. frequency
  @param barCount  Bars count
  */
  Spectrum(const unsigned int minFreq, const unsigned int maxFreq, const unsigned int barCount);

  /**
  @brief Create an empty spectrum with a custom refresh delay.

  @see initialize to construct the texture.

  @param minFreq      Min. frequency
  @param maxFreq      Max. frequency
  @param barCount    Bars count
  @param refreshDelay Refresh delay
  */
  Spectrum(const unsigned int minFreq, const unsigned int maxFreq, const unsigned int barCount, const int refreshDelay);
  ~Spectrum();

  virtual void update(const Sint16* stream, const int length, const float delta) override;
  virtual void onInitialization() override;

  /**
  @brief Get the average normalized amplitude for a center frequency and a range.

  Use this to detect a "beat" into a frequency range.

  @param frequency  Center frequency
  @param range      Range

  @return Normalized amplitude
  */
  float getNormalizedFrequencyAmplitude(const unsigned int frequency, const unsigned int range);

  /**
  @brief Get the bar count.

  @return Bar count
  */
  unsigned int getBarCount();

private:
  /// @brief Minimum frequency
  unsigned int _minFreq;
  /// @brief Maximum frequency
  unsigned int _maxFreq;
  /// @brief Bar count
  unsigned int _barCount;

  /// @brief Raw complex values
  Complex* _rawValues;
  ///@brief FFT values
  std::vector<float> _fftValues;
  ///@brief Bar values
  std::vector<float> _barValues;
  ///@brief Normalized bar values
  std::vector<float> _normalizedBarValues;
  ///@brief Bar frequencies
  std::vector<unsigned int> _barFrequencies;

  /**
  @brief Get the center frequency for the next bar, using an octave value.

  @param centerFreq Current center frequency
  @param octaves    Octave value

  @return Next center frequency
  */
  int nextCenterFreq(const int centerFreq, const float octaves);

  /**
  @brief Get the center frequency for the previous bar, using an octave value.

  @param centerFreq Current center frequency
  @param octaves    Octave value

  @return Previous center frequency
  */
  int prevCenterFreq(const int centerFreq, const float octaves);

  /**
  @brief Get the lower frequency limit for the current bar, using an octave value.

  @param centerFreq Current center frequency
  @param octaves    Octave value

  @return Lower frequency limit
  */
  int lowerLimit(const int centerFreq, const float octaves);

  /**
  @brief Get the lower frequency limit sample index for the current bar,
  e.g. the sample index into the stream, for an octave value and a
  sample length.

  @param centerFreq Current center frequency
  @param octaves    Octave value

  @return Lower frequency limit sample index
  */
  int lowerLimitSample(const int centerFreq, const float octaves, const int samplesLength);

  /**
  @brief Get the upper frequency limit for the current bar, using an octave value.

  @param centerFreq Current center frequency
  @param octaves    Octave value

  @return Upper frequency limit
  */
  int upperLimit(const int centerFreq, const float octaves);

  /**
  @brief Get the upper frequency limit sample index for the current bar,
  e.g. the sample index into the stream, for an octave value and a
  sample length.

  @param centerFreq Current center frequency
  @param octaves    Octave value

  @return Upper frequency limit sample index
  */
  int upperLimitSample(const int centerFreq, const float octaves, const int samplesLength);

  /**
  @brief Calculate the average frequency between a low and hi index interval.

  @param values Bar values
  @param low    Low frequency index
  @param hi     High frequency index

  @return Average frequency
  */
  float averageFreq(const std::vector<float>& values, const int low, const int hi);

  /**
  @brief Calculate the octave value, using a low frequency limit and a
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
