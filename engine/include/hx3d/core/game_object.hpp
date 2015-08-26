/*
    Game Object.
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

#ifndef HX3D_CORE_GAMEOBJECT
#define HX3D_CORE_GAMEOBJECT

#include "hx3d/graphics/batch.hpp"
#include "hx3d/graphics/utils/transform.hpp"

#include "hx3d/utils/ptr.hpp"

#include <string>
#include <vector>

namespace hx3d {

class GameObject {
public:
  GameObject(std::string name);
  GameObject(std::string name, unsigned int id);
  GameObject(std::string name, Ptr<GameObject> parent);
  GameObject(std::string name, Ptr<GameObject> parent, unsigned int id);

  virtual ~GameObject();

  /**
  Set the game object parent.
  @param parent GameObject (Ptr)
  */
  void setParent(Ptr<GameObject> parent);
  /**
  Set the game object parent.
  @param parent GameObject
  */
  void setParent(GameObject* parent);

  /**
  Get the game object ID.
  @return ID
  */
  unsigned int getId();

  /**
  Get the game object name.
  @return Name
  */
  std::string getName();

  /**
  Get the game object full transform from its parents.
  @return Full transform
  */
  Transform fullTransform();

  /**
  Add a child.
  @param object GameObject (Ptr)
  */
  void addChild(Ptr<GameObject> object);

  /**
  Get the children.
  @return Children
  */
  std::vector<Ptr<GameObject>>& getChildren();

  virtual void update();
  virtual void draw(Batch& batch);

  ///////////////////////////

  Transform transform;

private:
  GameObject* _parent;
  unsigned int _id;
  std::string _name;

  std::vector<Ptr<GameObject>> _children;
};

} /* hx3d */

#endif
