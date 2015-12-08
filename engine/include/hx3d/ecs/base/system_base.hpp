/*
    Entity Component System: Base System.
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

#ifndef HX3D_ECS_SYSTEMBASE
#define HX3D_ECS_SYSTEMBASE

#include "hx3d/ecs/component.hpp"
#include "hx3d/ecs/entity.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace ecs {

template <class EntityType>
class EngineBase;

template <class EntityType>
class SystemBase {
public:
  SystemBase();

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
  @param delta Delta time
  */
  virtual void process(const Ptr<EntityType>& entity, const float delta) = 0;

  /**
  Check if an entity can be processed (using the required family).

  @param bits Entity bits
  */
  bool canProcess(const unsigned int bits);

  /**
  Get the engine instance.

  @return Engine instance
  */
  EngineBase<EntityType>* getEngine();

  friend class EngineBase<EntityType>;

private:
  EngineBase<EntityType>* _engine;
  unsigned int _requiredFamily;
};

#include "hx3d/ecs/base/_inline/system_base.inl.hpp"

} /* ecs */
} /* hx3d */

#endif
