/*
    Base Batch Class.
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

#ifndef HX3D_GRAPHICS_BASEBATCH
#define HX3D_GRAPHICS_BASEBATCH

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
class BaseBatch {

public:
  BaseBatch();

  /**
  @brief Begin the batching.
  */
  virtual void begin() = 0;

  /**
  @brief End the batching.
  */
  virtual void end() = 0;

  /**
  @brief Draw the mesh.

  You must have called @link begin @endlink before.

  @param mesh Mesh
  */
  virtual void draw(Mesh& mesh) = 0;

  /**
  @brief Draw the text.

  You must have called @link begin @endlink before.

  @param text Text
  */
  virtual void draw(gui::Text& text) = 0;

  /**
  @brief Draw the text following a function.

  You must have called @link begin @endlink before.

  @param text   Text
  @param function  Function
  */
  virtual void draw(gui::Text& text, math::Function function) = 0;

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

  /**
  @brief Get the camera.

  @return camera Camera
  */
  Camera* getCamera();

protected:
  /// @brief Camera
  Camera* _camera;
  /// @brief Shader
  Ptr<Shader> _shader;
};

} /* graphics */
} /* hx3d */

#endif
