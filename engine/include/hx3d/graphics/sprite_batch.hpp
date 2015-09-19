/*
    Sprite batch.
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

#ifndef HX3D_GRAPHICS_SPRITEBATCH
#define HX3D_GRAPHICS_SPRITEBATCH

#include "hx3d/graphics/mesh.hpp"
#include "hx3d/graphics/multi_mesh.hpp"
#include "hx3d/graphics/multi_sprite.hpp"

#include "hx3d/gui/text.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Shader;
class Camera;
class SpriteBatch {

public:
  SpriteBatch();

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

  @param mesh MultiSprite
  */
  void draw(MultiSprite& sprite);

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

  @param camera Camera
  */
  void setCamera(Camera& camera);

private:
  Camera* _camera;
  Ptr<Shader> _shader;

  MultiMesh _mesh;
  unsigned int _lastIndex;

  Ptr<Texture> _lastTexture;
};

} /* hx3d */

#endif
