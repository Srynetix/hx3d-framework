/*
    Entity Component System: System.
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

#ifndef HX3D_ECS_SYSTEM
#define HX3D_ECS_SYSTEM

#include "hx3d/ecs/component.hpp"
#include "hx3d/ecs/entity.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace ecs {

class Engine;
class System {
public:
  System();

  /**
  Set the required component types for the system.
  @param Types Suite of Component types
  */
  template <class... Types>
  void setRequiredFamily() {
    _requiredFamily = ComponentBits::getFamily<Types...>();
  }

  /**
  Process an entity.
  Does not check if the entity can be processed.
  See @link#canProcess.

  @param entity Entity (Ptr)
  */
  virtual void process(Ptr<Entity> entity) = 0;

  /**
  Check if an entity can be processed (using the required family).
  @param bits Entity bits
  */
  bool canProcess(unsigned int bits);

  /**
  Get the engine instance.
  @return Engine instance
  */
  Engine* getEngine();

  friend class Engine;

private:
  Engine* _engine;
  unsigned int _requiredFamily;
};

} /* ecs */
} /* hx3d */

#endif
