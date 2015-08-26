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

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/string.hpp"

namespace hx3d {

SceneGraph::SceneGraph():
  _root(Make<GameObject>(""))
{
  _indexes["/"] = _root;
}

void SceneGraph::add(std::string path, Ptr<GameObject> object) {
  if (object->getName() == "") {
    Log.Error("SceneGraph: you can't add an unnamed game object.");
    return;
  }

  if (!testPath(path))
    return;

  Ptr<GameObject> parent = buildPath(path);
  object->setParent(parent);

  std::string object_path = path;
  if (path == "/") {
    object_path += object->getName();
  } else {
    object_path += "/" + object->getName();
  }

  _indexes[object_path] = object;
}

Ptr<GameObject> SceneGraph::get(std::string path) {

  if (testPath(path) && isIndex(path))
    return _indexes[path];

  return nullptr;
}

void SceneGraph::showEntries() {
  Log.Info("-- BEGIN Scene Graph Entries");
  for (auto& pair: _indexes) {
    Log.Info("Path: %s", pair.first.c_str());
  }
  Log.Info("-- END Scene Graph Entries");
}

/////////////////////////

Ptr<GameObject> SceneGraph::buildPath(std::string path) {

  if (!testPath(path))
    return nullptr;
  if (path == "/")
    return _root;

  std::vector<std::string> folders = split(path, '/');
  folders.erase(folders.begin());

  std::string current_path = "";
  Ptr<GameObject> last_go = nullptr;
  for (std::string s: folders) {
    current_path += "/" + s;

    if (!isIndex(current_path)) {
      if (last_go == nullptr) {
        last_go = Make<GameObject>(s);
        _indexes[current_path] = last_go;
      }
      else {
        Ptr<GameObject> current_go = Make<GameObject>(s, last_go);
        _indexes[current_path] = current_go;

        last_go = current_go;
      }
    } else {
      last_go = _indexes[current_path];
    }
  }

  return last_go;
}

bool SceneGraph::testPath(std::string path) {
  if (path.size() == 0 || path[0] != '/') {
    Log.Error("SceneGraph: trying to build a relative path: %s", path.c_str());
    return false;
  }

  std::vector<std::string> folders = split(path, '/');
  folders.erase(folders.begin());

  for (std::string s: folders) {
    if (s == "") {
      Log.Error("SceneGraph: empty folder name.");
      return false;
    }
  }

  return true;
}

bool SceneGraph::isIndex(std::string index) {
  return _indexes.find(index) != _indexes.end();
}

} /* hx3d */
