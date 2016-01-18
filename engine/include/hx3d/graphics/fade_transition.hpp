/*
    Fade screen transition.
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

#ifndef HX3D_GRAPHICS_FADETRANSITION
#define HX3D_GRAPHICS_FADETRANSITION

#include "hx3d/graphics/transition.hpp"
#include "hx3d/graphics/color.hpp"

namespace hx3d {
namespace graphics {

/**
@brief Color fading transition.
*/
class FadeTransition: public Transition {
public:
  /**
  @brief Create a fading transition with a color

  @param game   Game (Raw ptr)
  @param color  Color
  */
  FadeTransition(window::Game* game, Color color = Color::Black);

  virtual void render(Batch& batch, Framebuffer& currentFB, Framebuffer& nextFB) override;

  virtual void onUpdate(float delta) override;
  virtual void onDone() override;
  virtual void onStart() override;

private:
  Color _color;
};

} /* graphics */
} /* hx3d */

#endif /* HX3D_GRAPHICS_FADETRANSITION */
