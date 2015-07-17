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

#ifndef HX3D_GRAPHICS_VIEWPORT
#define HX3D_GRAPHICS_VIEWPORT

#include <glm/vec2.hpp>

#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Camera;
class Viewport {

public:
  Viewport();
  virtual ~Viewport();

  /**
  Set the viewport position.

  @param x X coordinate
  @param y Y coordinate
  */
  void setScreenPosition(float x, float y);

  /**
  Set the viewport camera.
  @param camera Camera (Ptr)
  */
  void setCamera(Ptr<Camera> camera);
  /**
  Get the viewport camera.
  @return Camera (Ptr)
  */
  Ptr<Camera> getCamera();

  /**
  Apply the viewport on the screen without centering the camera.
  */
  void apply();
  /**
  Apply the viewport on the screen with or without centering the camera.
  @param centerCamera Center camera ?
  */
  void apply(bool centerCamera);

  /**
  Update the viewport with a new screen width and height without centering
  the camera.

  @param screenWidth  New width
  @param screenHeight New height
  */
  void update(int screenWidth, int screenHeight);
  /**
  Update the viewport with a new screen width and height with or without
  centering the camera.

  @param screenWidth  New width
  @param screenHeight New height
  @param centerCamera Center camera ?
  */
  void update(int screenWidth, int screenHeight, bool centerCamera);

  /**
  Get the world size.
  */
  glm::vec2 getWorldSize();

protected:
  Ptr<Camera> _camera;
  float _worldWidth;
  float _worldHeight;

  int _screenX;
  int _screenY;
  int _screenWidth;
  int _screenHeight;

  /**
  Update the viewport with or without centering the camera (internal).
  @param centerCamera Center camera ?
  */
  virtual void internalUpdate(bool centerCamera) = 0;

};

} /* hx3d */

#endif
