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

#ifndef HX3D_ECS_SYSTEM
#define HX3D_ECS_SYSTEM

#include "hx3d/ecs/component.hpp"
#include "hx3d/ecs/entity.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace ecs {

class Entity;
class Engine;
/**
@brief Entity processing systems.

Matches entities with family filtering.
*/
class System {
public:
  System();

  /**
  @brief Set the required component types for the system.
  */
  template <class... Types>
  void setRequiredFamily();

  /**
  @brief Process an entity.
  Does not check if the entity can be processed.

  @see canProcess

  @param entity Entity (Ptr)
  @param delta Delta time
  */
  virtual void process(const Ptr<Entity>& entity, const float delta) = 0;

  /**
  @brief Check if an entity can be processed (using the required family).

  @param bits Entity bits

  @return True/False
  */
  bool canProcess(const unsigned int bits);

  /**
  @brief Get the engine instance.

  @return Engine instance
  */
  Engine* getEngine();

  friend class Engine;

private:
  /// @brief Engine link
  Engine* _engine;
  /// @brief Required family
  unsigned int _requiredFamily;
};

} /* ecs */
} /* hx3d */

#include "hx3d/ecs/_inline/system.inl.hpp"

#endif
