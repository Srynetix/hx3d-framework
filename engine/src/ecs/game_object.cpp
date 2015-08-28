/*
    Entity Component System: Game Object.
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

#include "hx3d/ecs/game_object.hpp"

namespace hx3d {
namespace ecs {

GameObject::GameObject(std::string name):
  EntityBase(0), _name(name), _graph(nullptr), _parent(nullptr)
  {}

Transform GameObject::getFullTransform() {
  if (_parent == nullptr) {
    return transform;
  }

  return transform.add(_parent->getFullTransform());
}

void GameObject::removeChild(std::string name) {
  if (!childNameExists(name)) {
    Log.Error("GameObject: child `%s` does not exists.", name.c_str());
    return;
  }

  Ptr<GameObject> obj = getChild<GameObject>(name);
  _graph->remove(obj->getPath());
}

std::string GameObject::getPath() {
  std::string path = _name;
  Ptr<GameObject> cursor = _parent;
  while (cursor != nullptr) {

    // Root
    if (cursor->_parent == nullptr) {
      path = "/" + path;
    }
    else {
      path = cursor->_name + "/" + path;
    }

    cursor = cursor->_parent;
  }

  return path;
}

/////////////////////

bool GameObject::childNameExists(std::string name) {
  for (Ptr<GameObject> o: _children) {
    if (o->_name == name) {
      return true;
    }
  }

  return false;
}

} /* ecs */
} /* hx3d */
