/*
    Matrix queue.
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

#ifndef HX3D_UTILS_MATRIXQUEUE
#define HX3D_UTILS_MATRIXQUEUE

#include <glm/mat4x4.hpp>
#include <queue>

namespace hx3d {

class MatrixQueue {

public:
  MatrixQueue();

  /**
  Remove the first matrix.
  */
  void pop();

  /**
  Get the first matrix.

  @return Matrix (mat4)
  */
  glm::mat4 get();

  /**
  Set the first matrix.

  @param mat Matrix (mat4)
  */
  void set(glm::mat4 mat);

  /**
  Push a new identity matrix at the top.
  */
  void push();

  /**
  Get the first matrix.

  @return Matrix (mat4)
  */
  operator glm::mat4();

  /**
  Set the first matrix.

  @param mat Matrix (mat4)
  @return Matrix (mat4)
  */
  MatrixQueue operator=(const glm::mat4& mat);

private:
  std::queue<glm::mat4> _matrices;
};

} /* hx3d */

#endif
