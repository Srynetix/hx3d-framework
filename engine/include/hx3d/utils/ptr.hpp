/*
    Smart pointers management.
    It's a simple suite of usings for fast writing.

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

#include <memory>

#define HX3D_PTR(klass) \
public: \
  using Ptr = Pointer<klass>;

namespace hx3d {

/**
@brief Quick-typing shared ptr
*/
template <class T>
using Pointer = std::shared_ptr<T>;

/**
@brief Quick-typing unique ptr
*/
template <class T>
using UPointer = std::unique_ptr<T>;

/**
@brief Quick-typing enable shared from this
*/
template <class T>
using EnableSharedThis = std::enable_shared_from_this<T>;

/**
@brief Quick-typing make shared
*/
template <class T, class... Args>
Pointer<T> Make(Args&&... args) {
  return std::make_shared<T>(args...);
}

} /* hx3d */
