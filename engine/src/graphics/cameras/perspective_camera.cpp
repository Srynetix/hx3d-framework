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

#include "hx3d/graphics/cameras/perspective_camera.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace graphics {

PerspectiveCamera::PerspectiveCamera(const float near, const float far):
  PerspectiveCamera(Core::App()->getWidth(), Core::App()->getHeight(), near, far)
{}

PerspectiveCamera::PerspectiveCamera(const float width, const float height, const float near, const float far):
  PerspectiveCamera(width, height, near, far, 70)
{}

PerspectiveCamera::PerspectiveCamera(const float width, const float height, const float near, const float far, const float fov):
  Camera(width, height, near, far), fieldOfView(fov)
{
  update();
}

void PerspectiveCamera::update() {
  float aspect = viewportWidth / viewportHeight;
  projection = glm::perspective(fieldOfView, aspect, near, far);
  //
  // for (int j = 0; j < 4; ++j) {
  //   for (int i = 0; i < 4; ++i) {
  //     Log.Info("[%d][%d]: %f", i, j, projection[i][j]);
  //   }
  // }

  view = glm::lookAt(position, position + direction, up);
}

} /* graphics */
} /* hx3d */
