/*
    Entity Component System: Base ID.
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

#include "hx3d/ecs/base/id_base.hpp"

namespace hx3d {
namespace ecs {

IDBase::IDBase(const unsigned int id): _id(id) {}
IDBase::~IDBase() {}

unsigned int IDBase::getId() const {
  return _id;
}

void IDBase::setId(unsigned int id) {
  _id = id;
}

} /* ecs */
} /* hx3d */
