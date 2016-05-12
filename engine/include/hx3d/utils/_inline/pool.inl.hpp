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
    const Pointer<T>& p = Make<T>(args...);
    p->setId(i);

    _available.push(i);
    _content.push_back(p);
  }
}

template <class T>
Pool<T>::~Pool() {}

template <class T>
const Pointer<T>& Pool<T>::take() {
  if (_available.size() > 0) {
    const Pointer<T>& ptr = _content[_available.front()];
    _available.pop();
    _locked.insert(ptr->getId());

    ptr->reset();
    return ptr;
  }

  throw std::runtime_error("STOP");
}

template <class T>
void Pool<T>::release(const Pointer<T>& ptr) {
  unsigned int id = ptr->getId();
  if (_locked.find(id) != _locked.end()) {
    _locked.erase(id);
    _available.push(id);

    ptr->reset();
  }

  else {
    Log.Error("Pool: Ptr is not working.");
  }
}

template <class T>
const std::set<Pointer<T>>& Pool<T>::getWorking() {
  _working.clear();
  for (auto& i: _locked) {
    _working.insert(_content[i]);
  }

  return _working;
}

} /* hx3d */
