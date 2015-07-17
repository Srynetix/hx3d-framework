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


    TODO
    > Real batching (ie. 1 VBO for all the meshes for 1 texture)
*/

#ifndef HX3D_GRAPHICS_BATCH
#define HX3D_GRAPHICS_BATCH

#include "hx3d/graphics/mesh.hpp"

#include "hx3d/gui/text.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Shader;
class Camera;
class Batch {

public:
  Batch();

  /**
  Begin the batching.
  */
  void begin();

  /**
  End the batching.
  */
  void end();

  /**
  Draw the mesh.
  You must have called @link#begin before.

  @param mesh Mesh
  */
  void draw(Mesh& mesh);

  /**
  Draw the text.
  You must have called @link#begin before.

  @param text Text
  */
  void draw(gui::Text& text);

  /**
  Draw the text following a function.
  You must have called @link#begin before.

  @param text   Text
  @param function  Function
  */
  void draw(gui::Text& text, math::Function function);

  ///////////////////

  /**
  Set the shader for the next batching.
  @param shader Shader (Ptr)
  */
  void setShader(Ptr<Shader> shader);

  /**
  Get the current batching shader.
  @return Shader (Ptr)
  */
  Ptr<Shader> getShader();

  /**
  Set the camera for the next batching.
  @param camera Camera (Ptr)
  */
  void setCamera(Ptr<Camera> camera);

private:
  Ptr<Camera> _camera;
  Ptr<Shader> _shader;
};

} /* hx3d */

#endif
