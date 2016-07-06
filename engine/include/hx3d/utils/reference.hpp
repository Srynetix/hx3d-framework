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

#pragma once

#include "hx3d/utils/ptr.hpp"

#include <memory>

#define HX3D_PTR_REF(klass) \
public: \
  using Ptr = Pointer<klass>; \
  using Ref = PrivateReference<klass>; \
  \
  template <class... Args> \
  static Pointer<klass> Create(Args&&... args) { \
    return Pointer<klass>(new klass(args...)); \
  }

namespace hx3d {

template <class T>
class Reference {
public:
  template <class... Args>
  Reference(Args&&... args);

  T* operator->() const;
  T& operator*() const;
  operator Pointer<T>() const;

private:
  Pointer<T> _ptr;
};

template <class T>
class PrivateReference {
public:
  template <class... Args>
  PrivateReference(Args&&... args);

  T* operator->() const;
  T& operator*() const;
  Pointer<T>& get();

  template <class U,
          typename = typename std::enable_if<std::is_base_of<U, T>::value>::type>
  operator Pointer<U>();

private:
  Pointer<T> _ptr;
};

} /* hx3d */

#include "hx3d/utils/_inline/reference.inl.hpp"
