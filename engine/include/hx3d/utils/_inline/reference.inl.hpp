/*
    Reference management.
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

template <class T>
template <class... Args>
Reference<T>::Reference(Args&&... args) {
  if (!this->_ptr) {
    this->_ptr = Make<T>(args...);
  }
}

template <class T>
T* Reference<T>::operator->() const {
  return this->_ptr.operator->();
}

template <class T>
T& Reference<T>::operator*() const {
  return this->_ptr.operator*();
}

template <class T>
Reference<T>::operator Pointer<T>() const {
  return this->_ptr;
}

template <class T>
template <class... Args>
PrivateReference<T>::PrivateReference(Args&&... args) {
  if (!this->_ptr) {
    this->_ptr = T::Create(args...);
  }
}

template <class T>
T* PrivateReference<T>::operator->() const {
  return this->_ptr.operator->();
}

template <class T>
T& PrivateReference<T>::operator*() const {
  return this->_ptr.operator*();
}

template <class T>
Pointer<T>& PrivateReference<T>::get() {
  return this->_ptr;
}

template <class T>
template <class U, typename>
PrivateReference<T>::operator Pointer<U>() {
  return this->_ptr;
}


} /* hx3d */
