/*
    Property system.
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

namespace hx3d {

template <class T>
CallbackProperty<T>::CallbackProperty(const T& value, std::function<void(const T&, const T&)> func):
  _value(value), _func(func) {}

template <class T>
CallbackProperty<T>::operator T const&() const {
  return _value;
}

template <class T>
T& CallbackProperty<T>::operator=(const T& value) {
    _func(_value, value);

    _value = value;
    return _value;
}

///////

template <class T>
Property<T>::Property(const T& value):
  _value(value) {}

template <class T>
void Property<T>::addObserver(PropertyObserver<T>* observer) {
  _observers.push_back(observer);
}

template <class T>
Property<T>::operator T const&() const {
  return _value;
}

template <class T>
T& Property<T>::operator=(const T& value) {
  for (auto obs: _observers) {
    obs->observe(_value, value);
  }

  _value = value;
  return _value;
}

} /* hx3d */
