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

#ifndef HX3D_ECS_SCENEGRAPH
#define HX3D_ECS_SCENEGRAPH

#include <map>

#include "hx3d/ecs/game_object.hpp"

namespace hx3d {

class SceneGraph {

public:
  SceneGraph();

  void add(std::string path, Ptr<GameObject> object);
  Ptr<GameObject> get(std::string path);

  void showEntries();

private:

  Ptr<GameObject> buildPath(std::string path);

  bool testPath(std::string path);
  bool isIndex(std::string index);

  std::map<std::string, Ptr<GameObject>> _indexes;
  Ptr<GameObject> _root;
};

} /* hx3d */

#endif
