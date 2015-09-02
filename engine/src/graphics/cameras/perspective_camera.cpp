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
#include "hx3d/core/application.hpp"

namespace hx3d {

PerspectiveCamera::PerspectiveCamera(float near, float far):
  PerspectiveCamera(Core::App()->getWidth(), Core::App()->getHeight(), near, far)
{}

PerspectiveCamera::PerspectiveCamera(float width, float height, float near, float far):
  PerspectiveCamera(width, height, near, far, 70)
{}

PerspectiveCamera::PerspectiveCamera(float width, float height, float near, float far, float fov):
  Camera(width, height, near, far), fieldOfView(fov)
{
  update();
}

void PerspectiveCamera::update() {
  float aspect = viewportWidth / viewportHeight;
  projection = glm::perspective(fieldOfView, aspect, near, far);
  view = glm::lookAt(position, position + direction, up);
}

} /* hx3d */
