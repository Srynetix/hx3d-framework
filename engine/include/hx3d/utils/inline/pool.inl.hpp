/*
    Pool system.
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

#include "hx3d/utils/log.hpp"

namespace hx3d {

template <class T>
template <class... Args>
Pool<T>::Pool(unsigned int size, Args... args): size(size) {
  for (unsigned int i = 0; i < size; ++i) {
    Ptr<T> p = Make<T>(args...);
    _available.push(p);
  }
}

template <class T>
Pool<T>::~Pool() {}

template <class T>
Ptr<T> Pool<T>::take() {
  if (_available.size() > 0) {
    Ptr<T> ptr = _available.front();
    _available.pop();
    _locked.insert(ptr);

    ptr->reset();
    return ptr;
  }

  return nullptr;
}

template <class T>
void Pool<T>::release(Ptr<T> ptr) {
  if (_locked.find(ptr) != _locked.end()) {
    _locked.erase(ptr);
    _available.push(ptr);

    ptr->reset();
  }

  else {
    Log.Error("Pool: Ptr is not working.");
  }
}

template <class T>
std::set<Ptr<T>>& Pool<T>::getWorking() {
  return _locked;
}

} /* hx3d */
