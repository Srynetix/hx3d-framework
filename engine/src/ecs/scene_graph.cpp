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

#include "hx3d/ecs/scene_graph.hpp"
#include <stack>

namespace hx3d {
namespace ecs {

SceneGraph::SceneGraph():
  _root(Make<Node>("/"))
{
  _root->_parent = nullptr;
  _entityEnabled = false;
  _indices["/"] = _root;
}

SceneGraph::~SceneGraph() {}

void SceneGraph::setEntityMode(bool enabled) {
  _entityEnabled = enabled;
}

Ptr<Node> SceneGraph::getRoot() {
  return _root;
}

unsigned int SceneGraph::getNodeCount() {
  return _root->getChildCount();
}

void SceneGraph::addIndex(const Ptr<Node>& object) {
  const std::string& path = object->getPath();
  for (const auto& pair: _indices) {
    if (pair.first == object->_name) {
      Log.Error("SceneGraph: Index `%s` already exists !", path.c_str());
      return;
    }
  }

  _indices[path] = object;
}

void SceneGraph::showIndices() {
  Log.Info("-- Graph indices");
  for (const auto& pair: _indices) {
    Log.Info("\t%s: %s", pair.first.c_str(), pair.second->_name.c_str());
  }
}

void SceneGraph::draw(Batch& batch) {
  std::stack<Ptr<Node>> stack;
  stack.push(_root);

  while (!stack.empty()) {
    const Ptr<Node>& node = stack.top();
    stack.pop();

    node->draw(batch);

    for (const Ptr<Node>& child: node->_children) {
      stack.push(child);
    }
  }
}

void SceneGraph::update(const float delta) {
  std::stack<Ptr<Node>> stack;
  stack.push(_root);

  while (!stack.empty()) {
    const Ptr<Node>& node = stack.top();
    stack.pop();

    node->update(delta);

    for (const Ptr<Node>& child: node->_children) {
      stack.push(child);
    }
  }

  if (_entityEnabled) {
    _engine.update(delta);
  }
}

  /////////////////

void SceneGraph::remove(const std::string path) {
  if (_indices.find(path) == _indices.end()) {
    Log.Error("SceneGraph: Index `%s` does not exists.", path.c_str());
    return;
  }

  if (path == "/") {
    Log.Error("SceneGraph: Root object can not be removed.");
    return;
  }

  const Ptr<Node>& obj = _indices[path];
  const Ptr<Node>& parent = obj->_parent;
  for (const Ptr<Node>& child: obj->_children) {
    remove(child->getPath());
  }

  for (unsigned int i = 0; i < parent->_children.size(); ++i) {
    if (parent->_children[i] == obj) {
      parent->_children.erase(parent->_children.begin() + i);
    }
  }

  if (_entityEnabled) {
    _engine.removeEntity(obj);
  }

  _indices.erase(path);
}

Ptr<Node> SceneGraph::pathExists(const std::string path) {
  if (path.size() == 0 || path[0] != '/') {
    Log.Error("SceneGraph: ill-formed path: `%s`. Must start with `/`", path.c_str());
    return nullptr;
  }

  std::vector<std::string> folders = split(path, '/');
  folders.erase(folders.begin());

  Ptr<Node>& node = _root;
  while (folders.size() > 0) {
    const std::string folder = folders[0];

    if (!node->childNameExists(folder)) {
      return nullptr;
    }

    node = node->template getChild<Node>(folder);
    folders.erase(folders.begin());
  }

  return node;
}

} /* ecs */
} /* hx3d */
