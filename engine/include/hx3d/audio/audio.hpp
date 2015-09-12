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

#ifndef HX3D_AUDIO_AUDIO
#define HX3D_AUDIO_AUDIO

#include <SDL2/SDL_mixer.h>

#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace audio {

class Effect;
class AudioDevice {
public:
  /**
  Initialize the audio system.
  */
  AudioDevice();
  ~AudioDevice();

  ///////////////////////////////

  /**
  Register an effect on a channel.
  Use Audio::PostChannel to put on the post channel.

  @param channel  Channel
  @param effect   Effect
  */
  void registerEffect(int channel, Effect& effect);

  /**
  Clear all the effects for a channel.
  Use Audio::PostChannel to put on the post channel.

  @param channel Channel
  */
  void clearEffects(int channel);

  /**
  Get the audio device frequency rate.

  @return Frequency rate
  */
  unsigned int getFrequencyRate();

  /**
  Get the audio device sample size.
  It is used for WAV chunk loading.

  @return Sample size
  */
  unsigned int getSampleSize();

  static int PostChannel;

private:
  int _audioRate;
  int _audioChannels;
  Uint16 _audioFormat;
  int _bits;
  int _sampleSize;
  int _bufferSize;
};

} /* audio */
} /* hx3d */

#endif
