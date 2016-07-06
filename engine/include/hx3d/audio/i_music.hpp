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

#pragma once

#include <string>

namespace hx3d {
namespace audio {

/**
@brief Single music management.

Permit to play/stop one music.
*/
class IMusic {

public:
  /**
  @brief Create an uninitialized music.

  @see initialize.
  */
  IMusic();

  /**
  @brief Load a music from a path.

  @param pathToFile Path to audio file.
  */
  explicit IMusic(const std::string pathToFile);
  virtual ~IMusic();

  /**
  @brief Initialize a music with a path.

  @param pathToFile Path to audio file
  */
  virtual void initialize(const std::string pathToFile) = 0;

  /**
  @brief Play the music.
  */
  virtual void play() = 0;

  /**
  @brief Stop the music.
  */
  virtual void stop() = 0;

  /**
  @brief Test if the music is playing.
  */
  virtual bool isPlaying() = 0;
};

} /* audio */
} /* hx3d */
