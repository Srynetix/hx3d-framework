/*
    Base buffer.
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

namespace hx3d {
namespace graphics {
namespace buffers {

template <class T>
Buffer<T>::Buffer() {
  glGenBuffers(1, &_buf);
}

template <class T>
Buffer<T>::~Buffer() {
  glDeleteBuffers(1, &_buf);
}

template <class T>
GLuint Buffer<T>::getId() {
  return _buf;
}

template <class T>
void Buffer<T>::set(const std::vector<T>& values) {
  _vector.clear();
  _vector.resize(values.size());

  std::copy(values.begin(), values.end(), _vector.begin());
}

template <class T>
void Buffer<T>::add(const std::vector<T>& values) {
  size_t prevSize = _vector.size();
  _vector.resize(prevSize + values.size());

  std::copy(values.begin(), values.end(), _vector.begin() + prevSize);
}

template <class T>
T* Buffer<T>::data() {
  return _vector.data();
}

template <class T>
unsigned int Buffer<T>::size() {
  return _vector.size();
}

template <class T>
std::vector<T>& Buffer<T>::getVector() {
  return _vector;
}

template <class T>
T Buffer<T>::getValue(const unsigned int i) {
  return _vector[i];
}

template <class T>
void Buffer<T>::setValue(const unsigned int i, const T value) {
  _vector[i] = value;
}

template <class T>
void Buffer<T>::clear() {
  _vector.clear();
}

} /* buffers */
} /* graphics */
} /* hx3d */
