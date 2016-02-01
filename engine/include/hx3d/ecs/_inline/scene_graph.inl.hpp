/*
    Entity Component System: Base Scene Graph.
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
    Foundation, Inc., 51 Franklin Street, FiAfth Floor, Boston, MA  02110-1301
    USA
*/

#include "hx3d/ecs/node.hpp"

namespace hx3d {
namespace ecs {

template <class T, class... Args>
Ptr<T> SceneGraph::createAtRoot(Args... args) {
  const Ptr<T>& ptr = createNodeChild<T>(_root, args...);
  return ptr;
}

template <class T, class... Args>
Ptr<T> SceneGraph::create(const std::string path, Args... args) {
  const Ptr<Node>& container = pathExists(path);
  if (container == nullptr) {
    Log.Error("SceneGraph: could not create at `%s`.", path.c_str());
    return nullptr;
  }

  const Ptr<T>& ptr = createNodeChild<T>(container, args...);
  return ptr;
}

template <class T>
Ptr<T> SceneGraph::fetch(const std::string path) {
  return std::dynamic_pointer_cast<T>(_indices[path]);
}

template <class T, class... Args>
Ptr<T> SceneGraph::createNodeChild(const Ptr<Node>& container, Args... args) {
  const Ptr<T>& object = Make<T>(args...);
  auto obj_name = object->getName();
  if (container->childNameExists(obj_name)) {
    Log.Error("Node: a child of `%s` is already named `%s`.", container->_name.c_str(), obj_name.c_str());
    return nullptr;
  }

  object->_parent = container;
  container->_children.push_back(object);

  addIndex(object);

  if (_entityEnabled) {
    _engine.registerEntity(object);
  }

  return object;
}

} /* ecs */
} /* hx3d */
