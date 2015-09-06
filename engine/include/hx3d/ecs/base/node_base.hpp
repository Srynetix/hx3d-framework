/*
    Entity Component System: Base Node.
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

#ifndef HX3D_ECS_NODEBASE
#define HX3D_ECS_NODEBASE

#include "hx3d/ecs/base/id_base.hpp"

#include "hx3d/graphics/batch.hpp"
#include "hx3d/graphics/utils/transform.hpp"

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/log.hpp"

#include <string>
#include <vector>

namespace hx3d {
namespace ecs {

template <bool EntityEnabled>
class SceneGraphBase;

template <bool EntityEnabled>
class NodeBase: public IDBase, public EnableSharedThis<NodeBase<EntityEnabled>> {

public:
  /**
  Create a named Node.
  Should not be used directly.
  To create a Node, use a SceneGraph.
  See @link#SceneGraphBase::create or @link#SceneGraphBase::createAtRoot.

  @param name Name
  */
  NodeBase(std::string name);

  /**
  Create a new child Node, using the SceneGraph.

  @param T    Node type
  @param name Name
  @param args Arguments
  */
  template <class T, class... Args>
  Ptr<T> createChild(std::string name, Args... args);

  /**
  Get one child.

  @param T    Node type
  @param name Name
  */
  template <class T>
  Ptr<T> getChild(std::string name);

  /**
  Remove a child, using the SceneGraph.
  @param name Name
  */
  void removeChild(std::string name);

  /**
  Get the game object full transform.
  @return Full transform;
  */
  Transform getFullTransform();

  /**
  Get the game object full path from the root.
  @return Path
  */
  std::string getPath();

  /**
  Destroy the node.
  */
  void destroy();

  /**
  Get the recursive child count.
  @param Child count
  */
  unsigned int getChildCount();

  /**
  Draw the node.
  @param batch Batch
  */
  virtual void draw(Batch& batch);

  /**
  Update the node.
  */
  virtual void update();

  ///////////

  Transform transform;

  friend class SceneGraphBase<EntityEnabled>;

protected:
  std::string _name;
  SceneGraphBase<EntityEnabled>* _graph;
  Ptr<NodeBase<EntityEnabled>> _parent;

  std::vector<Ptr<NodeBase<EntityEnabled>>> _children;

  /**
  Test if the object have a child.
  @param name Name
  */
  bool childNameExists(std::string name);
};

} /* ecs */
} /* hx3d */

#include "hx3d/ecs/base/node_base.inl.hpp"

#endif
