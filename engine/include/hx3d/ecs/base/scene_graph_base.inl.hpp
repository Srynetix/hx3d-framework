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
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#include "hx3d/ecs/z_engine.hpp"

#include "hx3d/ecs/base/node_base.hpp"

#include <stack>

namespace hx3d {
namespace ecs {

template <bool EntityEnabled>
SceneGraphBase<EntityEnabled>::SceneGraphBase():
  _root(Make<NodeBase<EntityEnabled>>("/")),
  _engine(Make<ZEngine>())
{
  _root->_graph = this;
  _root->_parent = nullptr;

  _indices["/"] = _root;
}

template <bool EntityEnabled>
SceneGraphBase<EntityEnabled>::~SceneGraphBase() {
}

template <bool EntityEnabled>
Ptr<NodeBase<EntityEnabled>> SceneGraphBase<EntityEnabled>::getRoot() {
  return _root;
}

template <bool EntityEnabled>
unsigned int SceneGraphBase<EntityEnabled>::getNodeCount() {
  return _root->getChildCount();
}

template <bool EntityEnabled>
void SceneGraphBase<EntityEnabled>::addIndex(Ptr<NodeBase<EntityEnabled>> object) {
  std::string path = object->getPath();
  for (auto& pair: _indices) {
    if (pair.first == object->_name) {
      Log.Error("SceneGraphBase: Index `%s` already exists !", path.c_str());
      return;
    }
  }

  _indices[path] = object;
}

template <bool EntityEnabled>
void SceneGraphBase<EntityEnabled>::showIndices() {
  Log.Info("-- Graph indices");
  for (auto& pair: _indices) {
    Log.Info("\t%s: %s", pair.first.c_str(), pair.second->_name.c_str());
  }
}

template <bool EntityEnabled>
void SceneGraphBase<EntityEnabled>::draw(Batch& batch) {
  std::stack<Ptr<NodeBase<EntityEnabled>>> stack;
  stack.push(_root);

  while (!stack.empty()) {
    Ptr<NodeBase<EntityEnabled>> node = stack.top();
    stack.pop();

    node->draw(batch);

    for (Ptr<NodeBase<EntityEnabled>> child: node->_children) {
      stack.push(child);
    }
  }
}

template <>
inline void SceneGraphBase<false>::update() {
  std::stack<Ptr<NodeBase<false>>> stack;
  stack.push(_root);

  while (!stack.empty()) {
    Ptr<NodeBase<false>> node = stack.top();
    stack.pop();

    node->update();

    for (Ptr<NodeBase<false>> child: node->_children) {
      stack.push(child);
    }
  }
}

template <>
inline void SceneGraphBase<true>::update() {
  std::stack<Ptr<NodeBase<true>>> stack;
  stack.push(_root);

  while (!stack.empty()) {
    Ptr<NodeBase<true>> node = stack.top();
    stack.pop();

    node->update();

    for (Ptr<NodeBase<true>> child: node->_children) {
      stack.push(child);
    }
  }

  _engine->update();
}

  /////////////////

template <bool EntityEnabled>
template <class T, class... Args>
Ptr<T> SceneGraphBase<EntityEnabled>::createAtRoot(std::string name, Args... args) {
  Ptr<T> ptr = createNodeChild<T>(_root, name, args...);
  return ptr;
}

template <bool EntityEnabled>
template <class T, class... Args>
Ptr<T> SceneGraphBase<EntityEnabled>::create(std::string path, std::string name, Args... args) {
  Ptr<NodeBase<EntityEnabled>> container = pathExists(path);
  if (container == nullptr) {
    Log.Error("SceneGraph: could not create at `%s`.", path.c_str());
    return nullptr;
  }

  Ptr<T> ptr = createNodeChild<T>(container, name, args...);
  return ptr;
}

template <>
inline void SceneGraphBase<false>::remove(std::string path) {
  if (_indices.find(path) == _indices.end()) {
    Log.Error("SceneGraph: Index `%s` does not exists.", path.c_str());
    return;
  }

  if (path == "/") {
    Log.Error("SceneGraph: Root object can not be removed.");
    return;
  }

  Ptr<NodeBase<false>> obj = _indices[path];
  Ptr<NodeBase<false>> parent = obj->_parent;
  for (Ptr<NodeBase<false>> child: obj->_children) {
    this->remove(child->getPath());
  }

  for (unsigned int i = 0; i < parent->_children.size(); ++i) {
    if (parent->_children[i] == obj) {
      parent->_children.erase(parent->_children.begin() + i);
    }
  }

  _indices.erase(path);
}

template <>
inline void SceneGraphBase<true>::remove(std::string path) {
  if (_indices.find(path) == _indices.end()) {
    Log.Error("SceneGraphBase: Index `%s` does not exists.", path.c_str());
    return;
  }

  if (path == "/") {
    Log.Error("SceneGraphBase: Root object can not be removed.");
    return;
  }

  Ptr<NodeBase<true>> obj = _indices[path];
  Ptr<NodeBase<true>> parent = obj->_parent;
  for (Ptr<NodeBase<true>> child: obj->_children) {
    remove(child->getPath());
  }

  for (unsigned int i = 0; i < parent->_children.size(); ++i) {
    if (parent->_children[i] == obj) {
      parent->_children.erase(parent->_children.begin() + i);
    }
  }

  // ...
  _engine->removeEntity(std::dynamic_pointer_cast<ZNode>(obj));

  _indices.erase(path);
}

template <bool EntityEnabled>
template <class T>
Ptr<T> SceneGraphBase<EntityEnabled>::fetch(std::string path) {
  return std::dynamic_pointer_cast<T>(_indices[path]);
}

template <bool EntityEnabled>
Ptr<NodeBase<EntityEnabled>> SceneGraphBase<EntityEnabled>::pathExists(std::string path) {
  if (path.size() == 0 || path[0] != '/') {
    Log.Error("SceneGraph: ill-formed path: `%s`. Must start with `/`", path.c_str());
    return nullptr;
  }

  std::vector<std::string> folders = split(path, '/');
  folders.erase(folders.begin());

  Ptr<NodeBase<EntityEnabled>> node = _root;
  while (folders.size() > 0) {
    std::string folder = folders[0];

    if (!node->childNameExists(folder)) {
      return nullptr;
    }

    node = node->template getChild<NodeBase<EntityEnabled>>(folder);
    folders.erase(folders.begin());
  }

  return node;
}

template <>
template <class T, class... Args>
Ptr<T> SceneGraphBase<false>::createNodeChild(Ptr<NodeBase<false>> container, std::string name, Args... args) {

  if (container->childNameExists(name)) {
    Log.Error("Node: a child of `%s` is already named `%s`.", container->_name.c_str(), name.c_str());
    return nullptr;
  }

  Ptr<T> object = Make<T>(name, args...);
  object->_parent = container;
  object->_graph = this;
  container->_children.push_back(object);

  addIndex(object);
  return object;
}

template <>
template <class T, class... Args>
Ptr<T> SceneGraphBase<true>::createNodeChild(Ptr<NodeBase<true>> container, std::string name, Args... args) {

  if (container->childNameExists(name)) {
    Log.Error("Node: a child of `%s` is already named `%s`.", container->_name.c_str(), name.c_str());
    return nullptr;
  }

  Ptr<T> object = Make<T>(name, args...);
  object->_parent = container;
  object->_graph = this;
  container->_children.push_back(object);

  addIndex(object);
  _engine->registerEntity(object);
  return object;
}

} /* ecs */
} /* hx3d */
