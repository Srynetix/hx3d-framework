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


    TODO
    > Finish the class.
*/

#ifndef HX3D_GRAPHICS_TEXTUREREGION
#define HX3D_GRAPHICS_TEXTUREREGION

#include <glm/vec2.hpp>

#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Texture;
class TextureRegion {

public:
  /**
  Create a texture region from a texture and rectangle coordinates.
  
  @param texture  Texture (Ptr)
  @param minX     Left coordinate
  @param maxX     Width
  @param minY     Top coordinate
  @param maxY     Height
  */
  TextureRegion(Ptr<Texture> texture, float minX, float maxX, float minY, float maxY);

private:
  Ptr<Texture> _texture;
  float _minX;
  float _maxX;
  float _minY;
  float _maxY;

  glm::vec2 _uv;
};

} /* hx3d */

#endif
