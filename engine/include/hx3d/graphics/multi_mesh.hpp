/*
    Multi mesh.
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

#ifndef HX3D_GRAPHICS_MULTIMESH
#define HX3D_GRAPHICS_MULTIMESH

#include "hx3d/graphics/color.hpp"

#include "hx3d/graphics/utils/multi_vbo.hpp"
#include "hx3d/graphics/utils/transform.hpp"

namespace hx3d {

class Shader;
class MultiMesh: public MultiVBO {

public:
  MultiMesh();

  /**
  Draw the mesh using a shader.

  @param shader Shader (Ptr)
  */
  virtual void draw(Ptr<Shader> shader);

  /**
  Set the mesh tint.
  Automatically update the color.
  See @link#updateColor.

  @param tint Color
  */
  void setTint(Color tint);

  /**
  Get the mesh tint.

  @return Tint
  */
  Color& getTint();

  /**
  Update the mesh color from the tint.
  */
  void updateColor();

  Transform transform;

protected:

  Color _tint;
};

} /* hx3d */

#endif
