/*
    Entity Component System: Engine.
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

#ifndef HX3D_ECS_ENGINE
#define HX3D_ECS_ENGINE

#include "hx3d/ecs/entity_base.hpp"

#include "hx3d/ecs/component.hpp"
#include "hx3d/ecs/system.hpp"

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/log.hpp"

#include <map>
#include <typeindex>
#include <functional>

namespace hx3d {
namespace ecs {

template <class E>
class Engine {

public:
  Engine();

  /**
  Create a new entity with the last entity id available.
  @return Entity (Ptr)
  */
  Ptr<E> createEntity();

  /**
  Affect an ID to a uninitialized entity.
  @param entity Entity (Ptr)
  */
  void registerEntity(Ptr<E> entity);

  /**
  Mark the entity for deletion from the engine.
  The deletion is delayed until the next update.

  @param entity Entity (Ptr)
  */
  void removeEntity(Ptr<E> entity);

  /**
  Get the component for an entity.

  @param T      Component type
  @param entity Entity (Ptr)
  */
  template <class T>
  Ptr<T> getComponent(Ptr<E> entity);

  /**
  Add a component for an entity.

  @param T          Component type
  @param entity     Entity (Ptr)
  @param component  Component (Ptr)
  */
  template <class T>
  void addComponent(Ptr<E> entity, Ptr<Component> component);

  /**
  Create a component for an entity with variable args.

  @param T      Component type
  @param entity Entity (Ptr)
  @param args   Arguments
  */
  template <class T, class... Args>
  void createComponent(Ptr<E> entity, Args... args);

  /**
  Add a system to the engine.

  @param T    System type
  @param sys  System (Ptr)
  */
  template <class T>
  void addSystem(Ptr<System<E>> sys);

  /**
  Create a system into the engine.

  @param T    System type
  @param args Arguments
  */
  template <class T, class... Args>
  void createSystem(Args... args);

  /**
  Get the number of components for an entity.

  @param entity Entity (Ptr)
  @return Number of components
  */
  unsigned int getComponentSize(Ptr<E> entity);

  /**
  Get the bits corresponding to the entity components.

  @param entity Entity (Ptr)
  @return Entity components bits
  */
  unsigned int getBits(Ptr<E> entity);

  /**
  Register a callback for a certain component type when it's added.

  @param T        Component type
  @param callback Callback function
  */
  template <class T>
  void registerComponentAdded(std::function<void(Ptr<Component>, Ptr<E>)> callback);

  /**
  Register a callback for a certain component type when it's removed.

  @param T        Component type
  @param callback Callback function
  */
  template <class T>
  void registerComponentRemoved(std::function<void(Ptr<Component>, Ptr<E>)> callback);

  /**
  Update the engine.
  */
  void update();

  /**
  Remove everything from the engine.
  */
  void clear();

private:
  std::map<unsigned int, Ptr<E>> _entities;
  std::map<unsigned int, std::map<std::type_index, Ptr<Component>>> _components;
  std::map<unsigned int, Bitset> _bits;

  std::map<std::type_index, Ptr<System<E>>> _systems;
  std::map<std::type_index, std::function<void(Ptr<Component>, Ptr<E>)>> _onComponentAdded;
  std::map<std::type_index, std::function<void(Ptr<Component>, Ptr<E>)>> _onComponentRemoved;

  std::vector<unsigned int> _toRemove;

  /**
  Remove all entities and their components.
  */
  void cleanEntities();

  /**
  Get the last entity id available.
  @return Last id available
  */
  unsigned int lastEntityAvailable();

  /**
  Add a component to an entity (internal).

  @param T          Component type
  @param entityId   Entity ID
  @param component  Component (Ptr)
  */
  template <class T>
  void addInternalComponent(unsigned int entityId, Ptr<Component> component);

  /**
  Remove all components for an entity.
  @param entityId   Entity id
  */
  void removeComponents(unsigned int entityId);
};

#include "hx3d/ecs/engine.inl"

} /* ecs */
} /* hx3d */

#endif
