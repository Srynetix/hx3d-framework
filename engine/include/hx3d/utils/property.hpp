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

#include <functional>

namespace hx3d {

template <class T>
class PropertyObserver {
public:
    virtual void observe(const T& current, const T& newVal) = 0;
};

template <class T>
class CBProperty {
private:
    T _value;
    std::function<void(const T&, const T&)> _func;

public:
    CBProperty(const T& value):
        CBProperty(value, nullptr) {}
    CBProperty(const T& value, std::function<void(const T&, const T&)> func):
        _value(value), _func(func) {}

    operator T const&() const {
        return _value;
    }

    T& operator=(const T& value) {
        if (_func)
            _func(_value, value);

        _value = value;
        return _value;
    }
};

template <class T>
class Property {
private:
    T _value;
    PropertyObserver<T>* _observer;

public:
    Property(const T& value):
        Property(value, nullptr) {}
    Property(const T& value, PropertyObserver<T>* observer):
        _value(value), _observer(observer) {}

    void setObserver(const PropertyObserver<T>* observer) {
        _observer = observer;
    }

    operator T const&() const {
        return _value;
    }

    T& operator=(const T& value) {
        if (_observer)
            _observer->observe(_value, value);
        _value = value;
        return _value;
    }
};

} /* hx3d */

#endif /* HX3D_UTILS_PROPERTY */
