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

#ifndef HX3D_GRAPHICS_CAMERA
#define HX3D_GRAPHICS_CAMERA

#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "hx3d/graphics/color.hpp"

namespace hx3d {

class Camera {
public:
  /**
  Create a camera with a viewport width and height.

  @param width  Viewport width
  @param height Viewport height
  @param near   Near
  @param far    Far
  */
  Camera(float width, float height, float near, float far);

  /**
  Look at target.
  @param target Target
  */
  void lookAt(glm::vec3 target);

  /**
  Translate the camera.
  @param vec Quantity
  */
  void translate(glm::vec3 vec);

  /**
  Rotate the camera on one/multiple axes.

  @param angle Angle in degrees
  @param axis  Direction(s)
  */
  void rotate(float angle, glm::vec3 axis);

  /**
  Rotate the camera around one point, on one/multiple axes.

  @param center Point
  @param angle  Angle in degrees
  @param axis   Direction(s)
  */
  void rotateAround(glm::vec3 center, float angle, glm::vec3 axis);

  /**
  Update the camera.
  */
  virtual void update() = 0;

  //////////////////

  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 up;

  glm::mat4 projection;
  glm::mat4 view;

  float near;
  float far;

  float viewportWidth;
  float viewportHeight;

};

} /* hx3d */

#endif
