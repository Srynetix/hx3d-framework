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

#include "hx3d/window/i_application.hpp"

namespace hx3d {
namespace window {

IApplication::IApplication() {}
IApplication::~IApplication() {}

int IApplication::getWidth() {
  return _width;
}

int IApplication::getHeight() {
  return _height;
}

glm::ivec2 IApplication::getSize() {
  return glm::ivec2(_width, _height);
}

float IApplication::getFPS() {
  return _currentFPS;
}

float IApplication::getDeltaTime() {
  return _deltaTime;
}

float IApplication::getElapsedTime() {
  return _elapsedTime;
}

} /* window */
} /* hx3d */
