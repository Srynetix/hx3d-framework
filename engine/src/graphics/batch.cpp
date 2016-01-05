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
  Shader::disable();
}

void Batch::setCamera(Camera& camera) {
  _camera = &camera;
}

void Batch::draw(Mesh& mesh) {

  glm::mat4 model = mesh.transform.compute();
  _shader->setUniformMatrix4f("u_modelview", _camera->view * model);

  mesh.draw(_shader);
}

void Batch::draw(gui::Text& text) {

  Texture::use(text.getFont(), text.getCharacterSize());

  Ptr<Shader> prevShader = _shader;

  setShader(text.getFont()->getShader());
  begin();

  float oldX = text.transform.position.x;

  if (text.isCenterAligned())
    text.transform.position.x -= text.getLength() / 2;

  glm::mat4 model = text.transform.compute();
  text.transform.position.x = oldX;

  _shader->setUniformMatrix4f("u_modelview", _camera->view * model);

  text.draw(_shader);

  setShader(prevShader);
  begin();

  Texture::disable();
}

void Batch::draw(gui::Text& text, math::Function function) {
  Texture::use(text.getFont(), text.getCharacterSize());

  Ptr<Shader> prevShader = _shader;

  setShader(text.getFont()->getShader());
  begin();

  float oldX = text.transform.position.x;

  if (text.isCenterAligned())
    text.transform.position.x -= text.getLength() / 2;

  glm::mat4 model = text.transform.compute();
  text.transform.position.x = oldX;

  _shader->setUniformMatrix4f("u_modelview", _camera->view * model);

  text.functionDraw(_shader, function);

  setShader(prevShader);
  begin();

  Texture::disable();
}

} /* graphics */
} /* hx3d */
