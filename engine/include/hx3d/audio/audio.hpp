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

namespace hx3d {
namespace audio {

class Audio {
public:
  Audio();
  ~Audio();

  unsigned int getFrequencyRate();
  unsigned int getSampleSize();

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
