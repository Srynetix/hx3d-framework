/*
    Entity Component System: Scene Graph.
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
#include "hx3d/ecs/game_object.hpp"

namespace hx3d {
namespace ecs {

SceneGraph::SceneGraph(): _root(Make<GameObject>("/")) {
  _root->_graph = this;
  _root->_parent = nullptr;

  _indices["/"] = _root;
}

SceneGraph::~SceneGraph() {
}

Ptr<GameObject> SceneGraph::getRoot() {
  return _root;
}

void SceneGraph::remove(std::string path) {
  if (_indices.find(path) == _indices.end()) {
    Log.Error("SceneGraph: Index `%s` does not exists.", path.c_str());
    return;
  }

  if (path == "/") {
    Log.Error("SceneGraph: Root object can not be removed.");
    return;
  }

  Ptr<GameObject> obj = _indices[path];
  Ptr<GameObject> parent = obj->_parent;
  for (Ptr<GameObject> child: obj->_children) {
    remove(child->getPath());
  }

  for (unsigned int i = 0; i < parent->_children.size(); ++i) {
    if (parent->_children[i] == obj) {
      parent->_children.erase(parent->_children.begin() + i);
    }
  }

  _indices.erase(path);
}

void SceneGraph::addIndex(Ptr<GameObject> object) {
  std::string path = object->getPath();
  for (auto& pair: _indices) {
    if (pair.first == object->_name) {
      Log.Error("SceneGraph: Index `%s` already exists !", path.c_str());
      return;
    }
  }

  _indices[path] = object;
}

void SceneGraph::showIndices() {
  Log.Info("-- Graph indices");
  for (auto& pair: _indices) {
    Log.Info("\t%s: %s", pair.first.c_str(), pair.second->_name.c_str());
  }
}

} /* ecs */
} /* hx3d */
