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

#ifndef HX3D_ECS_SCENEGRAPH
#define HX3D_ECS_SCENEGRAPH

#include "hx3d/utils/ptr.hpp"
#include "hx3d/graphics/base_batch.hpp"
#include "hx3d/ecs/engine.hpp"

#include <string>
#include <map>

namespace hx3d {
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

  @param name Name
  @param args Arguments

  @return T (Ptr)
  */
  template <class T, class... Args>
  Ptr<T> createAtRoot(const std::string name, Args... args);

  /**
  @brief Create a game object at a path.

  @param path Path
  @param name Name
  @param args Arguments

  @return T (Ptr)
  */
  template <class T, class... Args>
  Ptr<T> create(const std::string path, const std::string name, Args... args);

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
  Ptr<T> fetch(const std::string path);

  /**
  @brief Get the root.

  @return Node (Ptr)
  */
  Ptr<Node> getRoot();

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
  void draw(graphics::BaseBatch& batch);

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
  Ptr<Node> _root;
  /// @brief Node indices
  std::map<std::string, Ptr<Node>> _indices;
  /// @brief Engine for entity management
  Engine _engine;
  /// @brief Is entity management enabled ?
  bool _entityEnabled;

  /**
  @brief Add an index to the graph.

  @param object Node (Ptr)
  */
  void addIndex(const Ptr<Node>& object);

  /**
  @brief Test if the path exists and returns the node.

  @param path Path

  @return Node (Ptr)
  */
  Ptr<Node> pathExists(const std::string path);

  /**
  @brief Create a child for a container Node.

  @param container  Container node
  @param name       Child name
  @param args       Arguments

  @return Node (Ptr)
  */
  template <class T, class... Args>
  Ptr<T> createNodeChild(const Ptr<Node>& container, const std::string name, Args... args);
};

} /* ecs */
} /* hx3d */

#include "hx3d/ecs/_inline/scene_graph.inl.hpp"

#endif
