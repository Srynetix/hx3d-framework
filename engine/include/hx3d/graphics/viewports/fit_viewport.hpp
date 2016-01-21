/*
    Fit viewport.
    Inspired by LibGDX fit viewport.
    Automatically fit the rendering in the screen.

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

#ifndef HX3D_GRAPHICS_VIEWPORTS_FITVIEWPORT
#define HX3D_GRAPHICS_VIEWPORTS_FITVIEWPORT

#include "hx3d/graphics/viewports/viewport.hpp"

namespace hx3d {
namespace graphics {
namespace viewports {

/**
@brief Fit the screen resolution.
*/
class FitViewport: public Viewport {

public:

  /**
  @brief Create a fit viewport using a world width and height.

  @param worldWidth World width
  @param worldHeight World height
  */
  FitViewport(const float worldWidth, const float worldHeight);

  virtual void internalUpdate(Camera& camera) override;

};

} /* viewports */
} /* graphics */
} /* hx3d */

#endif
