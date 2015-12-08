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

#ifndef HX3D_ECS_SCENEGRAPHBASE
#define HX3D_ECS_SCENEGRAPHBASE

#include "hx3d/utils/ptr.hpp"

#include <string>
#include <map>

namespace hx3d {
namespace ecs {

template <bool EntityEnabled>
class NodeBase;

class ZEngine;

template <bool EntityEnabled>
class SceneGraphBase {
public:
  SceneGraphBase();
  ~SceneGraphBase();

  /**
  Create a game object at the root.

  @param T    Node type
  @param name Name
  @param args Arguments
  @return T (Ptr)
  */
  template <class T, class... Args>
  Ptr<T> createAtRoot(const std::string name, Args... args);

  /**
  Create a game object at a path.

  @param T    Node type
  @param path Path
  @param name Name
  @param args Arguments
  @return T (Ptr)
  */
  template <class T, class... Args>
  Ptr<T> create(const std::string path, const std::string name, Args... args);

  /**
  Remove a game object from a path.

  @param path Path
  */
  void remove(const std::string path);

  /**
  Fetch a game object from a path.

  @param T    Node type
  @param path Path
  @return T (Ptr)
  */
  template <class T>
  Ptr<T> fetch(const std::string path);

  /**
  Get the root.

  @return Node (Ptr)
  */
  Ptr<NodeBase<EntityEnabled>> getRoot();

  /**
  Get the number of nodes.

  @return Number of nodes
  */
  unsigned int getNodeCount();

  /**
  Show the graph indices.
  */
  void showIndices();

  /**
  Draw the nodes.

  @param batch Batch
  */
  void draw(Batch& batch);

  /**
  Update the nodes.

  @param delta Delta time
  */
  void update(const float delta);

  friend class NodeBase<EntityEnabled>;

protected:
  Ptr<NodeBase<EntityEnabled>> _root;
  std::map<std::string, Ptr<NodeBase<EntityEnabled>>> _indices;
  Ptr<ZEngine> _engine;

  /**
  Add an index to the graph.

  @param object Node (Ptr)
  */
  void addIndex(const Ptr<NodeBase<EntityEnabled>>& object);

  /**
  Test if the path exists and returns the node.

  @return Node (Ptr)
  */
  Ptr<NodeBase<EntityEnabled>> pathExists(const std::string path);

  /**
  Create a child for a container Node.

  @param T          Node type
  @param container  Container node
  @param name       Child name
  @param args       Arguments
  */
  template <class T, class... Args>
  Ptr<T> createNodeChild(const Ptr<NodeBase<EntityEnabled>>& container, const std::string name, Args... args);
};

} /* ecs */
} /* hx3d */

#include "hx3d/ecs/base/_inline/scene_graph_base.inl.hpp"

#endif
