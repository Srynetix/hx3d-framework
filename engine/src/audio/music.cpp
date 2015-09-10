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

#include "hx3d/audio/music.hpp"

#include "hx3d/utils/file.hpp"

namespace hx3d {
namespace audio {

Music::Music(): _music(nullptr), _file(nullptr) {}

Music::Music(std::string pathToFile) {
  create(pathToFile);
}

Music::~Music() {
  Mix_FreeMusic(_music);
}

void Music::create(std::string pathToFile) {
  _file = File::loadBinaryFile(pathToFile);

  SDL_RWops* musicOps = SDL_RWFromConstMem(_file->data, _file->size);
  _music = Mix_LoadMUS_RW(musicOps, 1);
}

void Music::play() {
  if (_music) {
    Mix_PlayMusic(_music, 1);
  }
}

void Music::stop() {
  if (_music) {
    Mix_HaltMusic();
  }
}

bool Music::isPlaying() {
  return Mix_PlayingMusic() != 0;
}

} /* audio */
} /* hx3d */
