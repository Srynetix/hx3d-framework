/*
    2D physics body definition.
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

#include "hx3d/physics/2d/body_def.hpp"

#include "hx3d/math/vector_utils.hpp"

namespace hx3d {
namespace physics2d {

b2BodyDef BodyDef::create(b2BodyType type, glm::vec2 position, float unitScale) {
  b2BodyDef def;
  def.type = type;
  def.position = math::convert(position / unitScale);

  return def;
}

} /* physics2d */
} /* hx3d */
