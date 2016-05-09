/*
    Viewport.
    Inspired by LibGDX viewport.

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


    TODO
    > Add more viewport types.
*/

#ifndef HX3D_GRAPHICS_VIEWPORTS_VIEWPORT
#define HX3D_GRAPHICS_VIEWPORTS_VIEWPORT

#include <glm/vec2.hpp>

#include "hx3d/graphics/cameras/camera.hpp"
#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace graphics {

/**
@brief Viewport types.
*/
namespace viewports {

/**
@brief Camera viewport.
*/
class Viewport {

public:
  Viewport();
  virtual ~Viewport();

  /**
  @brief Set the viewport position.

  @param x X coordinate
  @param y Y coordinate
  */
  void setScreenPosition(const float x, const float y);

  /**
  @brief Apply the viewport on the screen, centering the camera.

  @param camera Camera
  */
  void apply(const Ptr<Camera>& camera);

  /**
  @brief Update the viewport with a new screen width and height, centering
  the camera.

  @param camera       Camera
  @param screenWidth  New width
  @param screenHeight New height
  */
  void update(const Ptr<Camera>& camera, const int screenWidth, const int screenHeight);

  /**
  @brief Convert a screen point to a world point.

  @param screenPoint Screen point

  @return World point
  */
  glm::vec2 screenToWorld(const glm::vec2 screenPoint);

  /**
  @brief Get the world size.
  */
  glm::vec2 getWorldSize();

protected:
  /// @brief World width
  float _worldWidth;
  /// @brief World height
  float _worldHeight;

  /// @brief X offset
  int _screenX;
  /// @brief Y offset
  int _screenY;
  /// @brief Screen width
  int _screenWidth;
  /// @brief Screen height
  int _screenHeight;

  /**
  @brief Update the viewport, centering the camera (internal).
  */
  virtual void internalUpdate(const Ptr<Camera>& camera) = 0;
};

} /* viewports */
} /* graphics */
} /* hx3d */

#endif
