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
*/

#include "hx3d/graphics/viewports/viewport.hpp"

#include "hx3d/graphics/cameras/camera.hpp"
#include "hx3d/graphics/gl.hpp"

namespace hx3d {
namespace graphics {
namespace viewports {

Viewport::Viewport():
  _worldWidth(0), _worldHeight(0), _screenX(0), _screenY(0), _screenWidth(0), _screenHeight(0) {}

Viewport::~Viewport() {}

void Viewport::setScreenPosition(const float x, const float y) {
  _screenX = x;
  _screenY = y;
}

void Viewport::apply(const Pointer<Camera>& camera) {
  glViewport(_screenX, _screenY, _screenWidth, _screenHeight);

  camera->viewportWidth = _worldWidth;
  camera->viewportHeight = _worldHeight;

  // Centering
  camera->position = glm::vec3(_worldWidth / 2, _worldHeight / 2, camera->position.z);

  camera->update();
}

void Viewport::update(const Pointer<Camera>& camera, const int screenWidth, const int screenHeight) {
  _screenWidth = screenWidth;
  _screenHeight = screenHeight;

  internalUpdate(camera);
}

glm::vec2 Viewport::screenToWorld(const glm::vec2 screenPoint) {
  glm::vec2 worldPoint = glm::vec2(0);
  float ratioX = (_screenWidth / _worldWidth);
  float ratioY = (_screenHeight / _worldHeight);

  worldPoint.x = screenPoint.x / ratioX - _screenX / ratioX;
  worldPoint.y = screenPoint.y / ratioY - _screenY / ratioY;
  return worldPoint;
}

glm::vec2 Viewport::getWorldSize() {
  return glm::vec2(_worldWidth, _worldHeight);
}

} /* viewports */
} /* graphics */
} /* hx3d */
