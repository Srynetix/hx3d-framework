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

#include "hx3d/utils/matrix_queue.hpp"

namespace hx3d {

MatrixQueue::MatrixQueue() {
  _matrices.push(glm::mat4(1.f));
}

void MatrixQueue::pop() {
  _matrices.pop();
}

glm::mat4 MatrixQueue::get() {
  return _matrices.front();
}

void MatrixQueue::set(glm::mat4 mat) {
  _matrices.front() = mat;
}

void MatrixQueue::push() {
  _matrices.push(get());
}

MatrixQueue::operator glm::mat4() {
  return get();
}

MatrixQueue MatrixQueue::operator=(const glm::mat4& mat) {
  set(mat);

  return *this;
}

} /* hx3d */
