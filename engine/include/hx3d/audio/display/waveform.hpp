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

#include <SDL2/SDL_types.h>

#include "hx3d/graphics/image.hpp"
#include "hx3d/utils/timer.hpp"

namespace hx3d {
namespace audio {

class Waveform {
public:

  /**
  Create an empty waveform with a refresh delay of 50.
  See @link#create to construct the texture.
  */
  Waveform();

  /**
  Create an empty waveform with a custom refresh delay.
  See @link#create to construct the texture.
  @param refreshDelay Refresh delay
  */
  Waveform(int refreshDelay);
  ~Waveform();

  /**
  Create the waveform texture.
  @param width Width
  @param height Height
  */
  void create(unsigned int width, unsigned int height);

  /**
  Set the refresh delay.
  @param refreshDelay Refresh delay
  */
  void setRefreshDelay(float refreshDelay);

  /**
  Update the waveform.
  @param stream Stream of amplitudes (between 0 and 255)
  @param length Length of the stream
  */
  void update(Sint16* stream, int length);

  /**
  Get the texture (for displaying)
  @return Texture (Ptr)
  */
  Ptr<Texture> getTexture();

private:
  Image _image;
  Timer _timer;
  int _refreshDelay;
  bool _initialized;

  /**
  Draw a white box.
  */
  void drawBox();
};

} /* audio */
} /* hx3d */

#endif
