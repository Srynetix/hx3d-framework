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

#include "hx3d/graphics/cameras/camera.hpp"

namespace hx3d {
namespace graphics {

/**
@brief 3D perspective camera.
*/
class PerspectiveCamera: public Camera {
  HX3D_PTR(PerspectiveCamera)

public:
  /**
  @brief Create a perspective camera with the screen size and the near and far.

  The default field of view is 70.

  @param near Near
  @param far Far
  */
  PerspectiveCamera(const float near, const float far);

  /**
  @brief Create a perspective camera with a viewport width and height.

  The default field of view is 70.

  @param width  Viewport width
  @param height Viewport height
  @param near   Near
  @param far    Far
  */
  PerspectiveCamera(const float width, const float height, const float near, const float far);

  /**
  @brief Create a perspective camera with a viewport width and height,
  and a custom field of view.

  @param width  Viewport width
  @param height Viewport height
  @param near   Near
  @param far    Far
  @param fov    Field of view
  */
  PerspectiveCamera(const float width, const float height, const float near, const float far, const float fov);

  virtual void update() override;

  /// @brief Field of view (FOV)
  float fieldOfView;
};

} /* graphics */
} /* hx3d */

#endif
