/*
    Audio Converter: Signed Short.
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

#include "hx3d/audio/effect.hpp"

namespace hx3d {
namespace audio {

/**
@brief Convert an audio stream to the signed short format

<i>Example code</i>
@code
// Inside a create function...

// Converter creation
audio::S16Converter converter;

// Assign the converter as an effect over the main post channel
Core::Audio()->registerEffect(AudioDevice::PostChannel, converter);

[...]

// Inside an update function...

// If the converter has finished to convert
if (converter.hasProcessed()) {

  // Get the signed short stream and do whatever you want !
  short* stream = converter.getS16Stream();
}
@endcode
*/
class S16Converter: public Effect {
public:
  S16Converter();
  ~S16Converter();

  virtual void onFunction(const int channel, const void* stream, const int length) override;
  virtual void onDone(const int channel) override;

  /**
  @brief Get the stream in signed short format.

  @return Signed short stream
  */
  short* getS16Stream();
};

} /* audio */
} /* hx3d */
