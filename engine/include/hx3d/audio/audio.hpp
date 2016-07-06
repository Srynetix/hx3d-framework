/*
    Audio management.
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

#pragma once

namespace hx3d {

/**
  @brief Audio components
*/
namespace audio {

class Effect;

/**
  @brief Audio device management.

  Permit to register and clear effects.
*/
class AudioDevice {
public:
  AudioDevice();
  ~AudioDevice();

  ///////////////////////////////

  /**
  @brief Register an effect on a channel.

  Use Audio::PostChannel to put on the post channel.

  @param channel  Channel
  @param effect   Effect
  */
  void registerEffect(const int channel, Effect& effect);

  /**
  @brief Clear all the effects for a channel.

  Use Audio::PostChannel to put on the post channel.

  @param channel Channel
  */
  void clearEffects(const int channel);

  /**
  @brief Get the audio device frequency rate.

  @return Frequency rate
  */
  unsigned int getFrequencyRate();

  /**
  @brief Get the audio device sample size.

  It is used for WAV chunk loading.

  @return Sample size
  */
  unsigned int getSampleSize();

  /**
  @brief Post Channel Identifier
  */
  static int PostChannel;

private:
  /// @brief Device audio rate
  int _audioRate;
  /// @brief Device audio channels
  int _audioChannels;
  /// @brief Current audio format
  unsigned short _audioFormat;
  /// @brief Bits number
  int _bits;
  /// @brief Audio sample size
  int _sampleSize;
  /// @brief Audio buffer size
  int _bufferSize;
};

} /* audio */
} /* hx3d */
