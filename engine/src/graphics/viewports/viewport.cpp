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

Viewport::Viewport():
  _camera(nullptr), _worldWidth(0), _worldHeight(0), _screenX(0), _screenY(0), _screenWidth(0), _screenHeight(0) {}

Viewport::~Viewport() {}

void Viewport::setScreenPosition(float x, float y) {
  _screenX = x;
  _screenY = y;
}

void Viewport::setCamera(Camera& camera) {
  _camera = &camera;
}

Camera* Viewport::getCamera() {
  return _camera;
}

void Viewport::apply() {
  apply(false);
}

void Viewport::apply(bool centerCamera) {
  glViewport(_screenX, _screenY, _screenWidth, _screenHeight);

  _camera->viewportWidth = _worldWidth;
  _camera->viewportHeight = _worldHeight;

  if (centerCamera)
    _camera->position = glm::vec3(_worldWidth / 2, _worldHeight / 2, _camera->position.z);

  _camera->update();
}

void Viewport::update(int screenWidth, int screenHeight) {
  update(screenWidth, screenHeight, false);
}

void Viewport::update(int screenWidth, int screenHeight, bool centerCamera) {
  _screenWidth = screenWidth;
  _screenHeight = screenHeight;

  internalUpdate(centerCamera);
}

glm::vec2 Viewport::screenToWorld(glm::vec2 screenPoint) {
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

} /* hx3d */
