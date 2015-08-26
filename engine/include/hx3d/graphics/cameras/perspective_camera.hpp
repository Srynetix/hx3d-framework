/*
    Perspective camera.
    Inspired by LibGDX perspective camera.

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

#ifndef HX3D_GRAPHICS_CAMERAS_PERSPECTIVECAMERA
#define HX3D_GRAPHICS_CAMERAS_PERSPECTIVECAMERA

#include "hx3d/graphics/camera.hpp"

namespace hx3d {

class PerspectiveCamera: public Camera {
public:
  /**
  Create a perspective camera with the screen size.
  The default field of view is 70.
  */
  PerspectiveCamera();

  /**
  Create a perspective camera with a viewport width and height.
  The default field of view is 70.

  @param width  Viewport width
  @param height Viewport height
  */
  PerspectiveCamera(float width, float height);

  /**
  Create a perspective camera with a viewport width and height,
  and a custom field of view.

  @param width  Viewport width
  @param height Viewport height
  @param fov    Field of view
  */
  PerspectiveCamera(float width, float height, float fov);

  virtual void update() override;

  float fieldOfView;
};

} /* hx3d */

#endif
