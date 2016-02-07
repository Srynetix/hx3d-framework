/*
    Waveform display.
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

#ifndef HX3D_AUDIO_DISPLAY_WAVEFORM
#define HX3D_AUDIO_DISPLAY_WAVEFORM

#include "hx3d/audio/display.hpp"

namespace hx3d {
namespace audio {

/**
@brief Audio waveform displaying.

<i>Example code</i>
@code
// Inside a create function...

// Create a waveform
audio::Waveform waveform;

waveform.transform.position.x = 100;
waveform.transform.position.y = 100;

[...]

// Inside an update function...

// Get a signed short stream (see audio::S16Converter)
short* stream = s16converter.getS16Stream();

// Update the waveform
waveform.update(stream, s16converter.getSampleSize(), delta);

[...]

// Inside a render function...

// Display the waveform
batch.draw(waveform);
@endcode
*/
class Waveform: public Display {
public:

  /**
  @brief Create an empty waveform with a refresh delay of 50.

  @see initialize to construct the texture.
  */
  Waveform();

  /**
  @brief Create an empty waveform with a custom refresh delay.

  @see initialize to construct the texture.

  @param refreshDelay Refresh delay
  */
  Waveform(const int refreshDelay);
  ~Waveform();

  virtual void update(const Sint16* stream, const int length, const float delta) override;
};

} /* audio */
} /* hx3d */

#endif
