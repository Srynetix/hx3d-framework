/*
    Buffer attribute.
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

#include "hx3d/graphics/buffers/attribute.hpp"

namespace hx3d {

Attribute::Attribute():
  Attribute("", GL_INVALID_ENUM, 0) {}

Attribute::Attribute(std::string name, GLenum type, GLuint size):
  _name(name),
  _type(type),
  _size(size)
{}

const std::string Attribute::getName() const {
  return _name;
}

const GLenum Attribute::getType() const {
  return _type;
}

const GLuint Attribute::getSize() const {
  return _size;
}

} /* hx3d */
