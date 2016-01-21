/*
    Fit viewport.
    Inspired by LibGDX fit viewport.
    Automatically fit the rendering in the screen.

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

#include "hx3d/graphics/viewports/fit_viewport.hpp"

#include <cmath>

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace graphics {
namespace viewports {

FitViewport::FitViewport(const float worldWidth, const float worldHeight) {
  _worldWidth = worldWidth;
  _worldHeight = worldHeight;
}

void FitViewport::internalUpdate(Camera& camera) {
  float tgtRatio, srcRatio, scale;

  if (_screenWidth < _screenHeight) {
    tgtRatio = _screenWidth / _screenHeight;
    srcRatio = _worldWidth / _worldHeight;
    scale = tgtRatio > srcRatio ? _screenWidth / _worldWidth : _screenHeight / _worldHeight;
  } else {
    tgtRatio = _screenWidth / _screenHeight;
    srcRatio = _worldWidth / _worldHeight;
    scale = tgtRatio < srcRatio ? _screenWidth / _worldWidth : _screenHeight / _worldHeight;
  }

  int nx = std::floor(_worldWidth * scale);
  int ny = std::floor(_worldHeight * scale);

  _screenX = (_screenWidth - nx) / 2.f;
  _screenY = (_screenHeight - ny) / 2.f;
  _screenWidth = nx;
  _screenHeight = ny;

  apply(camera);
}

} /* viewports */
} /* graphics */
} /* hx3d */
