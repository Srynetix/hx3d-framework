/*
    Alpha fade screen transition.
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

#include "hx3d/graphics/transitions/transition.hpp"
#include "hx3d/graphics/color.hpp"

namespace hx3d {
namespace graphics {

/**
@brief Alpha fading transition.
*/
class AlphaFadeTransition: public Transition {
public:
  /**
  @brief Create a fading transition

  @param game   Game (Raw ptr)
  */
  AlphaFadeTransition(window::Game* game);

  virtual void render(const Pointer<Batch>& batch, const Pointer<Framebuffer>& currentFB, const Pointer<Framebuffer>& nextFB) override;

  virtual void onUpdate(float delta) override;
  virtual void onDone() override;
  virtual void onStart() override;
};

} /* graphics */
} /* hx3d */