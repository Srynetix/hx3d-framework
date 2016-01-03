/*
    Entity Component System: Node without entity information.
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

#ifndef HX3D_ECS_NODE
#define HX3D_ECS_NODE

#include "hx3d/ecs/entity.hpp"
#include "hx3d/utils/ptr.hpp"

#include "hx3d/graphics/transform.hpp"
#include "hx3d/graphics/batch.hpp"

namespace hx3d {

/**
@brief Entity-Component-System & Scene Graph components
*/
namespace ecs {

class SceneGraph;

/**
@brief Base node to use in a SceneGraph or an Engine.
*/
class Node: public Entity, public EnableSharedThis<Node> {
public:
  /**
  @brief Create a named Node.
  Should not be used directly.

  To create a Node, use a SceneGraph.

  @see SceneGraph::create
  @see SceneGraph::createAtRoot

  @param name Name
  */
  Node(const std::string name);

  /**
  @brief Create a new child Node, using the SceneGraph.

  @param T    Node type
  @param sg   SceneGraph
  @param name Name
  @param args Arguments
  */
  template <class T, class... Args>
  Ptr<T> createChild(SceneGraph& sg, const std::string name, Args... args);

  /**
  @brief Get one child.

  @param T    Node type
  @param name Name
  */
  template <class T>
  Ptr<T> getChild(const std::string name);

  /**
  @brief Remove a child, using the SceneGraph.

  @param sg SceneGraph
  @param name Name
  */
  void removeChild(SceneGraph& sg, const std::string name);

  /**
  @brief Get the game object full transform.

  @return Full transform;
  */
  Transform getFullTransform();

  /**
  @brief Get the game object full path from the root.

  @return Path
  */
  std::string getPath();

  /**
  @brief Destroy the node.

  @param sg SceneGraph
  */
  void destroy(SceneGraph& sg);

  /**
  @brief Get the recursive child count.

  @param Child count
  */
  unsigned int getChildCount();

  /**
  @brief Draw the node.

  @param batch Batch
  */
  virtual void draw(Batch& batch);

  /**
  @brief Update the node.

  @param delta Delta time
  */
  virtual void update(const float delta);

  ///////////

  /// @brief Current transform
  Transform transform;

  friend class SceneGraph;

protected:
  /// @brief Current name
  std::string _name;
  /// @brief Parent node
  Ptr<Node> _parent;
  /// @brief Children nodes
  std::vector<Ptr<Node>> _children;

  /**
  @brief Test if the object have a child.

  @param name Name
  */
  bool childNameExists(const std::string name);
};

} /* ecs */
} /* hx3d */

#include "hx3d/ecs/_inline/node.inl.hpp"

#endif
