/*
    Batch.
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

#include "hx3d/graphics/batch.hpp"

#include "hx3d/graphics/cameras/camera.hpp"

#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/font.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace graphics {

Batch::Batch():
  _camera(nullptr),
  _shader(nullptr)
{}

void Batch::setShader(const Ptr<Shader>& shader) {
  _shader = shader;
}

Ptr<Shader> Batch::getShader() {
  return _shader;
}

void Batch::begin() {
  if (_shader == nullptr) {
    Log.Error("Attempt to draw without shader.");
    return;
  }

  Shader::use(_shader);
  _shader->setUniformMatrix4f("u_projection", _camera->projection);
}

void Batch::end() {

  glDisable(GL_DEPTH_TEST);

  /**
  Meshes
  */
  for (auto& pair: _meshes) {
    auto& model = pair.first;
    Mesh& mesh = pair.second;

    _shader->setUniformMatrix4f("u_modelview", _camera->view * model);
    mesh.draw(_shader);
  }

  /**
  Function texts
  */
  for (auto& pair: _funcTexts) {
    gui::Text& text = pair.first;
    auto& func = pair.second;

    Texture::use(text.getFont(), text.getCharacterSize());

    float oldX = text.transform.position.x;
    if (text.isCenterAligned())
      text.transform.position.x -= text.getLength() / 2;

    glm::mat4 model = text.transform.compute();
    text.transform.position.x = oldX;

    auto& shader = text.getFont()->getShader();
    Shader::use(shader);
    shader->setUniformMatrix4f("u_modelview", _camera->view * model);
    shader->setUniformMatrix4f("u_projection", _camera->projection);
    text.functionDraw(shader, func);

    Shader::use(_shader);
    _shader->setUniformMatrix4f("u_projection", _camera->projection);

    Texture::disable();
  }

  /**
  Texts
  */
  for (gui::Text& text: _texts) {
    Texture::use(text.getFont(), text.getCharacterSize());

    float oldX = text.transform.position.x;
    if (text.isCenterAligned())
      text.transform.position.x -= text.getLength() / 2;

    glm::mat4 model = text.transform.compute();
    text.transform.position.x = oldX;

    auto& shader = text.getFont()->getShader();
    Shader::use(shader);
    shader->setUniformMatrix4f("u_modelview", _camera->view * model);
    shader->setUniformMatrix4f("u_projection", _camera->projection);
    text.draw(shader);

    Shader::use(_shader);
    _shader->setUniformMatrix4f("u_projection", _camera->projection);

    Texture::disable();
  }

  glEnable(GL_DEPTH_TEST);

  Shader::disable();
  _meshes.clear();
  _texts.clear();
  _funcTexts.clear();
}

void Batch::setCamera(Camera& camera) {
  _camera = &camera;
}

void Batch::draw(Mesh& mesh) {

  // glm::mat4 model = mesh.transform.compute();
  // _shader->setUniformMatrix4f("u_modelview", _camera->view * model);
  //
  // mesh.draw(_shader);

  unsigned int pos = 0;
  for (pos = 0; pos < _meshes.size(); ++pos) {
    auto& pair = _meshes[pos];
    Mesh& m = pair.second;

    if (m.transform.position.z > mesh.transform.position.z) {
      break;
    }
  }

  _meshes.insert(_meshes.begin() + pos, std::make_pair(mesh.transform.compute(), std::ref(mesh)));
}

void Batch::draw(gui::Text& text) {
  _texts.push_back(std::ref(text));
}

void Batch::draw(gui::Text& text, math::Function function) {
  _funcTexts.push_back(std::make_pair(std::ref(text), function));
}

} /* graphics */
} /* hx3d */
