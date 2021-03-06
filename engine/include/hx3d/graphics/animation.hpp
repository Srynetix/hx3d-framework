/*
    Animated sprite.
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

#ifndef HX3D_GRAPHICS_ANIMATION
#define HX3D_GRAPHICS_ANIMATION

#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/texture_atlas.hpp"

namespace hx3d {
namespace graphics {

/**
@brief Animated texture-atlas based sprite
*/
class Animation: public Sprite {
public:

  /**
  @brief Create an uninitialized animation.

  See @link initialize @endlink to create.
  */
  Animation();

  /**
  @brief Create an animation with an atlas, frames and a speed

  @param atlas  Texture atlas (Ptr)
  @param frames Frame names
  @param speed  Frame speed
  */
  Animation(Ptr<TextureAtlas> atlas, std::vector<std::string> frames, float speed);

  /**
  @brief Initialize an animation with an atlas, frames and a speed

  @param atlas  Texture atlas (Ptr)
  @param frames Frame names
  @param speed  Frame speed
  */
  void initialize(Ptr<TextureAtlas> atlas, std::vector<std::string> frames, float speed);

  /**
  @brief Update the animation

  @param delta Delta time
  */
  void update(float delta);

private:
  Ptr<TextureAtlas> _atlas;
  std::vector<std::string> _frames;

  float _currentTime;
  float _delay;
};

} /* graphics */
} /* hx3d */

#endif /* HX3D_GRAPHICS_ANIMATION */
