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

#pragma once

#include "hx3d/utils/ptr.hpp"
#include "hx3d/ecs/engine.hpp"

#include <string>
#include <set>
#include <map>

namespace hx3d {

namespace graphics {
  class Batch;
}

namespace ecs {

class Node;

/**
@brief Node management in hierarchy.

The SceneGraph is merged with an Engine, to do cross-entity management.
It is activable with @link setEntityMode @endlink.
*/
class SceneGraph {
public:
  SceneGraph();
  ~SceneGraph();

  /**
  @brief Create a game object at the root.

  @param args Arguments

  @return T (Ptr)
  */
  template <class T, class... Args>
  Pointer<T> createAtRoot(Args... args);

  /**
  @brief Create a game object at a path.

  @param path Path
  @param args Arguments

  @return T (Ptr)
  */
  template <class T, class... Args>
  Pointer<T> create(const std::string path, Args... args);

  /**
  @brief Remove a game object from a path.

  @param path Path
  */
  void remove(const std::string path);

  /**
  @brief Fetch a game object from a path.

  @param path Path

  @return T (Ptr)
  */
  template <class T>
  Pointer<T> fetch(const std::string path);

  /**
  @brief Get the root.

  @return Node (Ptr)
  */
  Pointer<Node> getRoot();

  /**
  @brief Get the number of nodes.

  @return Number of nodes
  */
  unsigned int getNodeCount();

  /**
  @brief Show the graph indices.
  */
  void showIndices();

  /**
  @brief Draw the nodes.

  @param batch Batch
  */
  void draw(const Pointer<graphics::Batch>& batch);

  /**
  @brief Update the nodes.

  @param delta Delta time
  */
  void update(const float delta);

  /**
  @brief Activate/Deactivate the entity management mode.

  @param enabled Enabled ?
  */
  void setEntityMode(bool enabled);

protected:
  /// @brief Graph root
  Pointer<Node> _root;
  /// @brief Node indices
  std::map<std::string, Pointer<Node>> _indices;
  /// @brief Engine for entity management
  Engine _engine;
  /// @brief Is entity management enabled ?
  bool _entityEnabled;

  /**
  @brief Add an index to the graph.

  @param object Node (Ptr)
  */
  void addIndex(const Pointer<Node>& object);

  /**
  @brief Test if the path exists and returns the node.

  @param path Path

  @return Node (Ptr)
  */
  Pointer<Node> pathExists(const std::string path);

  /**
  @brief Remove a node.

  @param node Node (Ptr)
  */
  void internalRemove(const Pointer<Node>& node);

  /**
  @brief Create a child for a container Node.

  @param container  Container node
  @param args       Arguments

  @return Node (Ptr)
  */
  template <class T, class... Args>
  Pointer<T> createNodeChild(const Pointer<Node>& container, Args... args);
};

} /* ecs */
} /* hx3d */

#include "hx3d/ecs/_inline/scene_graph.inl.hpp"
