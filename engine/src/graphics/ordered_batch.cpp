/*
    Ordered Batch.
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

#include "hx3d/graphics/ordered_batch.hpp"

#include "hx3d/graphics/cameras/camera.hpp"

#include "hx3d/core/core.hpp"

#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/font.hpp"

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/assets.hpp"

namespace hx3d {
namespace graphics {

OrderedBatch::OrderedBatch(): BaseBatch() {}

void OrderedBatch::begin() {
  if (_shader == nullptr) {
    Log.Error("Attempt to draw without shader.");
    return;
  }

  Shader::use(_shader);
  _shader->setUniformMatrix4f("u_projection", _camera->projection);
  _shader->setUniformMatrix4f("u_view", _camera->view);
}

void OrderedBatch::end() {

  /**
  Meshes
  */
  for (auto& pair: _meshes) {
    auto& model = pair.first;
    const Ptr<Mesh>& mesh = pair.second;

    _shader->setUniformMatrix4f("u_model", model);
    mesh->draw(_shader);
  }

  /**
  Function texts
  */
  for (auto& pair: _funcTexts) {
    auto& text = pair.first;
    auto& func = pair.second;

    Texture::use(text->getFont(), text->getCharacterSize());

    float oldX = text->transform.position.x;
    if (text->isCenterAligned())
      text->transform.position.x -= text->getLength() / 2;

    glm::mat4 model = text->transform.compute();
    text->transform.position.x = oldX;

    auto& shader = text->getFont()->getShader();
    Shader::use(shader);
    shader->setUniformMatrix4f("u_model", model);
    shader->setUniformMatrix4f("u_view", _camera->view);
    shader->setUniformMatrix4f("u_projection", _camera->projection);
    text->functionDraw(shader, func);

    Shader::use(_shader);
    _shader->setUniformMatrix4f("u_view", _camera->view);
    _shader->setUniformMatrix4f("u_projection", _camera->projection);

    Texture::disable();
  }

  /**
  Texts
  */
  for (auto& text: _texts) {
    Texture::use(text->getFont(), text->getCharacterSize());

    float oldX = text->transform.position.x;
    if (text->isCenterAligned())
      text->transform.position.x -= text->getLength() / 2;

    glm::mat4 model = text->transform.compute();
    text->transform.position.x = oldX;

    auto& shader = text->getFont()->getShader();
    Shader::use(shader);
    shader->setUniformMatrix4f("u_model", model);
    shader->setUniformMatrix4f("u_view", _camera->view);
    shader->setUniformMatrix4f("u_projection", _camera->projection);
    text->draw(shader);

    Shader::use(_shader);
    _shader->setUniformMatrix4f("u_view", _camera->view);
    _shader->setUniformMatrix4f("u_projection", _camera->projection);

    Texture::disable();
  }

  Shader::disable();
  _meshes.clear();
  _texts.clear();
  _funcTexts.clear();
}

void OrderedBatch::draw(const Ptr<Mesh>& mesh) {

  unsigned int pos = 0;
  for (pos = 0; pos < _meshes.size(); ++pos) {
    auto& pair = _meshes[pos];
    auto& m = pair.second;

    if (m->transform.position.z > mesh->transform.position.z) {
      break;
    }
  }

  _meshes.insert(_meshes.begin() + pos, std::make_pair(mesh->transform.compute(), mesh));
}

void OrderedBatch::draw(const Ptr<gui::Text>& text) {
  _texts.push_back(text);
}

void OrderedBatch::draw(const Ptr<gui::Text>& text, math::Function function) {
  _funcTexts.push_back(std::make_pair(text, function));
}

} /* graphics */
} /* hx3d */
