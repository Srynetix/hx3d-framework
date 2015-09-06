/*
    Entity Component System: Base Node.
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

#include "hx3d/ecs/base/scene_graph_base.hpp"

namespace hx3d {
namespace ecs {

template <bool EntityEnabled>
NodeBase<EntityEnabled>::NodeBase(std::string name):
  IDBase(0), _name(name), _graph(nullptr), _parent(nullptr)
{}

template <bool EntityEnabled>
Transform NodeBase<EntityEnabled>::getFullTransform() {
  if (_parent == nullptr) {
    return transform;
  }

  return transform.add(_parent->getFullTransform());
}

template <bool EntityEnabled>
void NodeBase<EntityEnabled>::removeChild(std::string name) {
  if (!childNameExists(name)) {
    Log.Error("Node: child `%s` does not exists.", name.c_str());
    return;
  }

  Ptr<NodeBase<EntityEnabled>> obj = getChild<NodeBase<EntityEnabled>>(name);
  _graph->remove(obj->getPath());
}

template <bool EntityEnabled>
std::string NodeBase<EntityEnabled>::getPath() {
  std::string path = _name;
  Ptr<NodeBase<EntityEnabled>> cursor = _parent;
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

template <bool EntityEnabled>
void NodeBase<EntityEnabled>::draw(Batch& batch) {
}

template <bool EntityEnabled>
void NodeBase<EntityEnabled>::update() {
}

template <bool EntityEnabled>
void NodeBase<EntityEnabled>::destroy() {
  _graph->remove(getPath());
}

template <bool EntityEnabled>
unsigned int NodeBase<EntityEnabled>::getChildCount() {
  
  unsigned int totalChildren = 0;
  for (auto child: _children) {
    totalChildren += child->getChildCount();
  }

  return totalChildren + _children.size();
}

/////////////////////

template <bool EntityEnabled>
bool NodeBase<EntityEnabled>::childNameExists(std::string name) {
  for (Ptr<NodeBase<EntityEnabled>> o: _children) {
    if (o->_name == name) {
      return true;
    }
  }

  return false;
}

///////////////////////

template <bool EntityEnabled>
template <class T, class... Args>
Ptr<T> NodeBase<EntityEnabled>::createChild(std::string name, Args... args) {
  return _graph->template createNodeChild<T>(this->shared_from_this(), name, args...);
}

template <bool EntityEnabled>
template <class T>
Ptr<T> NodeBase<EntityEnabled>::getChild(std::string name) {
  for (Ptr<NodeBase<EntityEnabled>> obj: _children) {
    if (obj->_name == name) {
      return std::dynamic_pointer_cast<T>(obj);
    }
  }

  Log.Error("Node: child `%s` does not exists.", name.c_str());
  return nullptr;
}

} /* ecs */
} /* hx3d */
