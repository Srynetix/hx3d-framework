/*
    Property.
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

#ifndef HX3D_UTILS_PROPERTY
#define HX3D_UTILS_PROPERTY

#include <vector>
#include <functional>

namespace hx3d {

/**
@brief Property observer (Observer pattern)
*/
template <class T>
class PropertyObserver {
public:
  /**
  @brief Observe property modification

  @param current  Current value
  @param newVal   New value
  */
  virtual void observe(const T& current, const T& newVal) = 0;
};

/**
@brief Callback-on-change property
*/
template <class T>
class CallbackProperty {
private:
  T _value;
  std::function<void(const T&, const T&)> _func;

public:
  /**
  @brief Create a callback property with value and function.

  @param value  Base value
  @param func   Callback function
  */
  CallbackProperty(const T& value, std::function<void(const T&, const T&)> func);

  /**
  @brief Get the value

  @return Value
  */
  operator T const&() const;

  /**
  @brief Set the value and start the callback

  @param value New value

  @return Modified value
  */
  T& operator=(const T& value);
};

/**
@brief Observable property
*/
template <class T>
class Property {
private:
  T _value;
  std::vector<PropertyObserver<T>*> _observers;

public:
  /**
  @brief Create an observable property with value

  @param value Base value
  */
  Property(const T& value);

  /**
  @brief Add an observer

  @param observer Observer
  */
  void addObserver(PropertyObserver<T>* observer);

  /**
  @brief Get the value

  @return Value
  */
  operator T const&() const;

  /**
  @brief Set the value and call the observers

  @param value New value

  @return Modified value
  */
  T& operator=(const T& value);
};

} /* hx3d */

#include "hx3d/utils/_inline/property.inl.hpp"

#endif /* HX3D_UTILS_PROPERTY */
