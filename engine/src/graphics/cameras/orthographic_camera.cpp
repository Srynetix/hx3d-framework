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

#include "hx3d/graphics/cameras/orthographic_camera.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/core/application.hpp"

namespace hx3d {

OrthographicCamera::OrthographicCamera():
  OrthographicCamera(Core::App()->getWidth(), Core::App()->getHeight())
{}

OrthographicCamera::OrthographicCamera(float width, float height):
  Camera(width, height), zoom(1.f)
  {
    near = -1.f;
    far = 1.f;

    position = glm::vec3(zoom * viewportWidth / 2.f, zoom * viewportHeight / 2.f, 0);

    update();
}

void OrthographicCamera::update() {
  projection = glm::ortho(zoom * (-viewportWidth / 2.f), zoom * (viewportWidth / 2.f), zoom * (-viewportHeight / 2.f), zoom * (viewportHeight / 2.f), near, far);

  view = glm::lookAt(position, position + direction, up);
}

void OrthographicCamera::setToOrtho(float width, float height) {
  position = glm::vec3(zoom * viewportWidth / 2.f, zoom * viewportHeight / 2.f, 0);

  viewportWidth = width;
  viewportHeight = height;
  update();
}

} /* hx3d */
