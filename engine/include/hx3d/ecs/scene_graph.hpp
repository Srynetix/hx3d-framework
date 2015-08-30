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

#include "hx3d/utils/ptr.hpp"

#include <string>
#include <map>

namespace hx3d {
namespace ecs {

class GameObject;
class SceneGraph {
public:
  SceneGraph();
  ~SceneGraph();

  /**
  Create a game object at the root.

  @param T    GameObject type
  @param name Name
  @param args Arguments
  @return T (Ptr)
  */
  template <class T, class... Args>
  Ptr<T> createAtRoot(std::string name, Args... args);

  /**
  Create a game object at a path.

  @param T    GameObject type
  @param path Path
  @param name Name
  @param args Arguments
  @return T (Ptr)
  */
  template <class T, class... Args>
  Ptr<T> create(std::string path, std::string name, Args... args);

  /**
  Remove a game object from a path.
  @param path Path
  */
  void remove(std::string path);

  /**
  Fetch a game object from a path.

  @param T    GameObject type
  @param path Path
  @return T (Ptr)
  */
  template <class T>
  Ptr<T> fetch(std::string path);

  /**
  Get the root.
  @return GameObject (Ptr)
  */
  Ptr<GameObject> getRoot();

  /**
  Show the graph indices.
  */
  void showIndices();

  friend class GameObject;

private:
  Ptr<GameObject> _root;
  std::map<std::string, Ptr<GameObject>> _indices;

  /**
  Add an index to the graph.
  @param object GameObject (Ptr)
  */
  void addIndex(Ptr<GameObject> object);
};

} /* ecs */
} /* hx3d */

#include "hx3d/ecs/scene_graph.inl.hpp"

#endif
