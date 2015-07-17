/*
    Entity Component System: Component.
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

#ifndef HX3D_ECS_COMPONENT
#define HX3D_ECS_COMPONENT

#include <map>
#include <typeindex>

#include "hx3d/utils/bitset.hpp"

namespace hx3d {
namespace ecs {

/**
Base component
*/
class Component {
public:
  Component();
  virtual ~Component();
};

/**
Unique bit attribution for each component
*/
class ComponentBits {
public:
  /**
    Get the bits for the current component type T.
    @param T Component type (must be a Component child type)
  */
  template <class T>
  static unsigned int get(typename std::enable_if<std::is_base_of<Component, T>::value>::type* test = nullptr);

  /**
    Get the bits corresponding to the suite of Types.
    @param Types Suite of Component types
    */
  template <class... Types>
  static unsigned int getFamily();

private:
  static std::map<std::type_index, unsigned int> _componentBits;
  static unsigned int _currentBit;

  /**
    Build a bitset corresponding to the suite of Types.
    @param Types Suite of Component types
    */
  template <class T, class... Types>
  static Bitset getFamilyInternal();
  template <class... Types>
  static Bitset getFamilyInternal(typename std::enable_if<sizeof...(Types) == 0>::type* test = nullptr);
};

#include "hx3d/ecs/component.inl"

} /* ecs */
} /* hx3d */

#endif
