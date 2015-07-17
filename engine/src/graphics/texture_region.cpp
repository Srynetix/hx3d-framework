/*
    Texture region.
    To delimit a texture rectangle.

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

#include "hx3d/graphics/texture_region.hpp"

#include "hx3d/graphics/texture.hpp"

namespace hx3d {

TextureRegion::TextureRegion(Ptr<Texture> texture, float minX, float maxX, float minY, float maxY):
  _texture(texture), _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY),
  _uv(0.f)
  {}

} /* hx3d */
