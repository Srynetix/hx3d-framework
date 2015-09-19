/*
    Sprite batch.
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

#include "hx3d/graphics/sprite_batch.hpp"

#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/camera.hpp"
#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/font.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {

SpriteBatch::SpriteBatch():
  _camera(nullptr),
  _shader(nullptr),
  _lastIndex(0),
  _lastTexture(nullptr)
{}

void SpriteBatch::setShader(Ptr<Shader> shader) {
  _shader = shader;
}

Ptr<Shader> SpriteBatch::getShader() {
  return _shader;
}

void SpriteBatch::begin() {
  if (_shader == nullptr) {
    Log.Error("Attempt to draw without shader.");
    return;
  }

  Shader::use(_shader);
  _shader->setUniformMatrix4f("u_projection", _camera->projection);

  _mesh.getMultiBuffer().clear();
  _mesh.getAttribute("Position").clear();
  _mesh.getAttribute("Color").clear();
  _mesh.getAttribute("Texture").clear();

  _mesh.getIndices().clear();
  _lastIndex = 0;
}

void SpriteBatch::end() {

  _shader->setUniformMatrix4f("u_modelview", _camera->view);

  // DRAW !

  _mesh.uploadAll();

  if (_lastTexture) {
    Texture::use(_lastTexture);
  }

  _mesh.draw(_shader);

  Texture::disable();
  Shader::disable();
}

void SpriteBatch::setCamera(Camera& camera) {
  _camera = &camera;
}

void SpriteBatch::draw(Sprite& mesh) {
  glm::mat4 model = mesh.transform.compute();
  _lastTexture = mesh.getTexture();

  std::vector<float> newPositions;
  std::vector<GLushort> newIndices;
  auto& buffer = mesh.getAttribute("Position");
  auto& meshIndices = mesh.getIndices();

  newPositions.resize(buffer.size());
  newIndices.resize(meshIndices.size());

  for (unsigned int i = 0; i < meshIndices.size(); ++i) {
    newIndices[i] = meshIndices.getValue(i) + _lastIndex;
  }

  for (unsigned int i = 0; i < buffer.size(); i += 3) {
    glm::vec4 pos(buffer.getValue(i), buffer.getValue(i+1), buffer.getValue(i+2), 1);
    pos = model * pos;

    newPositions[i] = pos.x;
    newPositions[i+1] = pos.y;
    newPositions[i+2] = pos.z;
  }

  // Positions OK !
  _mesh.getAttribute("Position").add(newPositions);
  _mesh.getAttribute("Texture").add(mesh.getAttribute("Texture").getVector());
  _mesh.getAttribute("Color").add(mesh.getAttribute("Color").getVector());

  _mesh.getIndices().add(newIndices);

  _lastIndex += newPositions.size() / 3;
}

} /* hx3d */
