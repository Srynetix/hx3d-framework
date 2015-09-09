/*
    Audio effect.
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

#ifndef HX3D_AUDIO_EFFECT
#define HX3D_AUDIO_EFFECT

#include <SDL2/SDL_mixer.h>

namespace hx3d {
namespace audio {

class Effect {
public:
  Effect();
  virtual ~Effect();

  virtual void onFunction(int channel, void* stream, int length);
  virtual void onDone(int channel);

  int getChannel();
  void* getStream();
  int getSampleSize();
  bool hasProcessed();

protected:
  bool _processed;
  int _channel;
  void* _stream;
  int _length;
};

} /* audio */
} /* hx3d */

#endif
