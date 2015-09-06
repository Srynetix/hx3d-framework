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

#include "hx3d/audio/audio.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {

Audio::Audio() {
  int flags = Mix_Init(~0);
  std::string types;

  if (flags & MIX_INIT_FLAC)
    types += "\t- FLAC\n";
  if (flags & MIX_INIT_MOD)
    types += "\t- MOD\n";
  if (flags & MIX_INIT_MP3)
    types += "\t- MP3\n";
  if (flags & MIX_INIT_OGG)
    types += "\t- OGG\n";
  if (!flags)
    types += "\t- None\n";

  Log.Info("Supported audio types: \n%s", types.c_str());

  /** Open device */
  _bufferSize = 1024;

  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, _bufferSize);
  Mix_QuerySpec(&_audioRate, &_audioFormat, &_audioChannels);

  _bits = _audioFormat & 0xFF;
  _sampleSize = _bits / 8 + _audioChannels;

  Log.Info(
    "Audio device information: \n\
    \t - %d Hz / %d bits / %s / %d bytes buffer. \n\
    \t - Sample size: %d\n",
  _audioRate, _bits, _audioChannels > 1 ? "Stereo" : "Mono", _bufferSize,
  _sampleSize);
}

Audio::~Audio() {
  Mix_Quit();
}

unsigned int Audio::getFrequencyRate() {
  return _audioRate;
}

unsigned int Audio::getSampleSize() {
  return _sampleSize;
}

} /* hx3d */