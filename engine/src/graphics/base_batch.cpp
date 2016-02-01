/*
    Base Batch Class.
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

#include "hx3d/graphics/base_batch.hpp"

#include "hx3d/graphics/cameras/camera.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/graphics/shader.hpp"

#include "hx3d/utils/assets.hpp"

namespace hx3d {
namespace graphics {

BaseBatch::BaseBatch():
  _camera(nullptr),
  _shader(Core::Assets()->get<Shader>("base"))
  {}

void BaseBatch::setShader(const Ptr<Shader>& shader) {
  _shader = shader;
}

Ptr<Shader> BaseBatch::getShader() {
  return _shader;
}

void BaseBatch::setCamera(Camera& camera) {
  _camera = &camera;
}

Camera* BaseBatch::getCamera() {
  return _camera;
}

} /* graphics */
} /* hx3d */
