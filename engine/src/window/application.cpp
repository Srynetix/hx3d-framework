/*
    Application management.
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

#include "hx3d/window/application.hpp"

namespace hx3d {
namespace window {

Application::Application(const Ptr<Game>& game, ApplicationConfig config):
  _game(game), _running(false),
  _width(config.width), _height(config.height), _fpsLimit(config.fpsLimit), _title(config.title),
  _elapsedTime(0)
  {}

Application::~Application() {}

int Application::getWidth() {
  return _width;
}

int Application::getHeight() {
  return _height;
}

glm::ivec2 Application::getSize() {
  return glm::ivec2(_width, _height);
}

float Application::getFPS() {
  return _currentFPS;
}

float Application::getElapsedTime() {
  return _elapsedTime;
}

} /* window */
} /* hx3d */
