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
*/

#ifndef HX3D_GRAPHICS_BATCH
#define HX3D_GRAPHICS_BATCH

#include "hx3d/graphics/mesh.hpp"
#include "hx3d/gui/text.hpp"
#include "hx3d/utils/ptr.hpp"

namespace hx3d {

/**
@brief 2D and 3D graphics components.
*/
namespace graphics {

class Shader;
class Camera;

/**
@brief Draw meshes and texts on screen.
*/
class Batch {

public:
  Batch();

  /**
  @brief Begin the batching.
  */
  void begin();

  /**
  @brief End the batching.
  */
  void end();

  /**
  @brief Draw the mesh.

  You must have called @link begin @endlink before.

  @param mesh Mesh
  */
  void draw(Mesh& mesh);

  /**
  @brief Draw the text.

  You must have called @link begin @endlink before.

  @param text Text
  */
  void draw(gui::Text& text);

  /**
  @brief Draw the text following a function.

  You must have called @link begin @endlink before.

  @param text   Text
  @param function  Function
  */
  void draw(gui::Text& text, math::Function function);

  ///////////////////

  /**
  @brief Set the shader for the next batching.

  @param shader Shader (Ptr)
  */
  void setShader(const Ptr<Shader>& shader);

  /**
  @brief Get the current batching shader.

  @return Shader (Ptr)
  */
  Ptr<Shader> getShader();

  /**
  @brief Set the camera for the next batching.

  @param camera Camera
  */
  void setCamera(Camera& camera);

private:
  /// @brief Camera
  Camera* _camera;
  /// @brief Shader
  Ptr<Shader> _shader;
};

} /* graphics */
} /* hx3d */

#endif
