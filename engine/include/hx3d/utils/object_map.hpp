/*
    Object map.
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

#ifndef HX3D_UTILS_OBJECT_MAP
#define HX3D_UTILS_OBJECT_MAP

#include "hx3d/utils/ptr.hpp"

#include <string>
#include <map>

namespace hx3d {

/**
@brief Map of whatever you want. Useful for user data.
*/
class ObjectMap {
  public:
    ObjectMap();

    /**
    @brief Get a named value

    @param name Key

    @return Value
    */
    template <class T>
    T* get(std::string name);

    /**
    @brief Set a named value

    @param name   Key
    @param object Value
    */
    template <class T>
    void set(std::string name, T* object);

  private:
    std::map<std::string, void*> _objects;
};

} /* hx3d */

#include "hx3d/utils/_inline/object_map.inl.hpp"

#endif /* HX3D_UTILS_OBJECT_MAP */
