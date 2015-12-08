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
namespace audio {

class Music {

public:
  /**
  Create an uninitialized music.
  See @link#initialize.
  */
  Music();

  /**
  Create an initialized music using a path.

  @param pathToFile Path to audio file.
  */
  explicit Music(const std::string pathToFile);
  ~Music();

  /**
  initialize a music with a path.

  @param pathToFile Path to audio file
  */
  void initialize(const std::string pathToFile);

  /**
  Play the music.
  */
  void play();

  /**
  Stop the music.
  */
  void stop();

  /**
  Test if the music is playing.
  */
  bool isPlaying();

private:
  Mix_Music* _music;
  Ptr<File> _file;
};

} /* audio */
} /* hx3d */

#endif
