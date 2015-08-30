/*
    2D physics collision matrix.
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

#ifndef HX3D_PHYSICS_2D_COLLISIONMATRIX
#define HX3D_PHYSICS_2D_COLLISIONMATRIX

#include <string>
#include <map>

namespace hx3d {
namespace physics2d {

class CollisionMatrix {
public:
  CollisionMatrix();

  /**
  Add a category.
  @param name Name
  */
  void addCategory(std::string name);

  /**
  Add a mask for a category from multiple categories.
  @param name   Category
  @param name   First category
  @param others Other categories
  */
  template <class... Categories>
  void addMask(std::string name, std::string category, Categories... others);
  template <class... Categories>
  void addMask(std::string name, std::string category, typename std::enable_if<sizeof...(Categories) == 0>::type* test = nullptr);

  /**
  Get a category bit from a name.
  @param category Category name
  */
  unsigned int getCategory(std::string category);
  /**
  Get a mask bit from a name.
  @param category Category name
  */
  unsigned int getMask(std::string category);

private:
  std::map<std::string, unsigned int> _categories;
  std::map<std::string, unsigned int> _masks;

  unsigned int _currentCategory;

  /**
  Add one mask for a category.
  @param name     Category
  @param category Other category
  */
  void addOneMask(std::string name, std::string category);
};

#include "hx3d/physics/2d/collision_matrix.inl.hpp"

} /* physics2d */
} /* hx3d */

#endif
