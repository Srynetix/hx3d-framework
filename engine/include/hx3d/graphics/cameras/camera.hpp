/*
    Base camera class.
    Inspired by LibGDX camera.

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

#ifndef HX3D_GRAPHICS_CAMERAS_CAMERA
#define HX3D_GRAPHICS_CAMERAS_CAMERA

#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "hx3d/graphics/color.hpp"

namespace hx3d {
namespace graphics {

/**
@brief 2D/3D camera.

@see OrthographicCamera
@see PerspectiveCamera
*/
class Camera {
  HX3D_PTR(Camera)
  
public:
  /**
  @brief Create a camera with a viewport width and height.

  @param width  Viewport width
  @param height Viewport height
  @param near   Near
  @param far    Far
  */
  Camera(const float width, const float height, const float near, const float far);

  /**
  @brief Look at target.

  @param target Target
  */
  void lookAt(glm::vec3 target);

  /**
  @brief Translate the camera.

  @param vec Quantity
  */
  void translate(const glm::vec3 vec);

  /**
  @brief Rotate the camera on one/multiple axes.

  @param angle Angle in degrees
  @param axis  Direction(s)
  */
  void rotate(const float angle, const glm::vec3 axis);

  /**
  @brief Rotate the camera around one point, on one/multiple axes.

  @param center Point
  @param angle  Angle in degrees
  @param axis   Direction(s)
  */
  void rotateAround(const glm::vec3 center, const float angle, const glm::vec3 axis);

  /**
  @brief Update the camera.
  */
  virtual void update() = 0;

  //////////////////

  /// @brief Camera position
  glm::vec3 position;
  /// @brief Camera direction
  glm::vec3 direction;
  /// @brief Camera up vector
  glm::vec3 up;

  /// @brief Projection matrix
  glm::mat4 projection;
  /// @brief View matrix
  glm::mat4 view;

  /// @brief Near pane
  float near;
  /// @brief Far pane
  float far;

  /// @brief Viewport width
  float viewportWidth;
  /// @brief Viewport height
  float viewportHeight;
};

} /* graphics */
} /* hx3d */

#endif
