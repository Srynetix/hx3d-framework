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

#include "hx3d/ecs/scene_graph.hpp"

namespace hx3d {
namespace ecs {

template <class T, class... Args>
Ptr<T> GameObject::createChild(std::string name, Args... args) {
  if (childNameExists(name)) {
    Log.Error("GameObject: a child of `%s` is already named `%s`.", _name.c_str(), name.c_str());
    return nullptr;
  }

  Ptr<T> object = Make<T>(name, args...);
  object->_parent = shared_from_this();
  object->_graph = _graph;
  _children.push_back(object);

  _graph->addIndex(object);

  return object;
}

template <class T>
Ptr<T> GameObject::getChild(std::string name) {
  for (Ptr<GameObject> obj: _children) {
    if (obj->_name == name) {
      return std::dynamic_pointer_cast<T>(obj);
    }
  }

  Log.Error("GameObject: child `%s` does not exists.", name.c_str());
  return nullptr;
}

} /* ecs */
} /* hx3d */
