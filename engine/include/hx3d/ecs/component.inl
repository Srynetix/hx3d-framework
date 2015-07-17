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

template <class T>
unsigned int ComponentBits::get(typename std::enable_if<std::is_base_of<Component, T>::value>::type* test) {
  auto& type = typeid(T);

  if (_componentBits.find(type) == _componentBits.end()) {
    _componentBits[type] = _currentBit++;
  }

  return _componentBits[type];
}

template <class... Types>
Bitset ComponentBits::getFamilyInternal(typename std::enable_if<sizeof...(Types) == 0>::type* test) {
  return Bitset();
}

template <class T, class... Types>
Bitset ComponentBits::getFamilyInternal() {
  Bitset bitset = getFamilyInternal<Types...>();
  bitset.set(ComponentBits::get<T>());
  return bitset;
}

template <class... Types>
unsigned int ComponentBits::getFamily() {
  return getFamilyInternal<Types...>().getBits();
}
