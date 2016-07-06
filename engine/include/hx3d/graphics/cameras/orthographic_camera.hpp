/*
    Orthographic camera.
    Inspired by LibGDX orthographic camera.

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

#include "hx3d/graphics/cameras/camera.hpp"
#include "hx3d/utils/reference.hpp"

namespace hx3d {
namespace graphics {

/**
@brief 2D orthographic camera w/ Z-buffer.
*/
class OrthographicCamera: public Camera {
  HX3D_PTR_REF(OrthographicCamera)

public:
  /**
  @brief Create an orthographic camera with the screen size.
  */
  OrthographicCamera();

  /**
  @brief Create an orthographic camera with a viewport width and height.

  @param width  Viewport width
  @param height Viewport height
  */
  OrthographicCamera(const float width, const float height);

  /**
  @brief Set the orthographic size.

  @param width  Viewport width
  @param height Viewport height
  */
  void setToOrtho(const float width, const float height);

  virtual void update() override;

  /// @brief Camera zoom
  float zoom;
};

} /* graphics */
} /* hx3d */
