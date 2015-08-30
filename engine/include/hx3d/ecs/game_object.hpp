/*
    Entity Component System: Game Object.
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

#ifndef HX3D_ECS_GAMEOBJECT
#define HX3D_ECS_GAMEOBJECT

#include "hx3d/ecs/entity_base.hpp"

#include "hx3d/graphics/utils/transform.hpp"
#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/log.hpp"

#include <string>
#include <vector>

namespace hx3d {
namespace ecs {

class SceneGraph;
class GameObject: public EntityBase, public EnableSharedThis<GameObject> {

public:
  /**
  Create a named GameObject.
  Should not be used directly.
  To create a GameObject, use a SceneGraph.
  See @link#SceneGraph::create or @link#SceneGraph::createAtRoot.

  @param name Name
  */
  GameObject(std::string name);

  /**
  Create a new child GameObject.

  @param T    GameObject type
  @param name Name
  @param args Arguments
  */
  template <class T, class... Args>
  Ptr<T> createChild(std::string name, Args... args);

  /**
  Get one child.

  @param T    GameObject type
  @param name Name
  */
  template <class T>
  Ptr<T> getChild(std::string name);

  /**
  Remove a child.
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

  ///////////

  Transform transform;

  friend class SceneGraph;

protected:
  std::string _name;
  SceneGraph* _graph;
  Ptr<GameObject> _parent;

  std::vector<Ptr<GameObject>> _children;

  /**
  Test if the object have a child.
  @param name Name
  */
  bool childNameExists(std::string name);
};

} /* ecs */
} /* hx3d */

#include "hx3d/ecs/game_object.inl.hpp"

#endif
