/*
    Music management.
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

#ifndef HX3D_AUDIO_MUSIC
#define HX3D_AUDIO_MUSIC

#include <SDL2/SDL_mixer.h>

#include "hx3d/utils/file.hpp"

namespace hx3d {

class Music {

public:
  Music();
  explicit Music(std::string pathToFile);
  ~Music();

  void play();
  void stop();
  bool isPlaying();

private:
  Mix_Music* _music;
  Ptr<File> _file;
};

} /* hx3d */

#endif
