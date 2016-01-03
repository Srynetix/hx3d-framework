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

/**
@brief Single music management.

Permit to play/stop one music.
*/
class Music {

public:
  /**
  @brief Create an uninitialized music.

  @see initialize.
  */
  Music();

  /**
  @brief Load a music from a path.

  @param pathToFile Path to audio file.
  */
  explicit Music(const std::string pathToFile);
  ~Music();

  /**
  @brief Initialize a music with a path.

  @param pathToFile Path to audio file
  */
  void initialize(const std::string pathToFile);

  /**
  @brief Play the music.
  */
  void play();

  /**
  @brief Stop the music.
  */
  void stop();

  /**
  @brief Test if the music is playing.
  */
  bool isPlaying();

private:
  /// @brief SDL_Mixer music
  Mix_Music* _music;
  /// @brief File pointer
  Ptr<File> _file;
};

} /* audio */
} /* hx3d */

#endif
