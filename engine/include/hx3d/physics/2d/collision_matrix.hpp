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

#pragma once

#include <string>
#include <map>

namespace hx3d {
namespace physics2d {

/**
@brief Collision matrix with masks and category
*/
class CollisionMatrix {
public:
  CollisionMatrix();

  /**
  @brief Add a category.

  @param name Name
  */
  void addCategory(std::string name);

  /**
  @brief Add a mask for a category from multiple categories.

  @param name     Category name
  @param category First category
  @param others   Other categories
  */
  template <class... Categories>
  void addMask(std::string name, std::string category, Categories... others);
  template <class... Categories>
  void addMask(std::string name, std::string category, typename std::enable_if<sizeof...(Categories) == 0>::type* test = nullptr);

  /**
  @brief Get a category bit from a name.

  @param category Category name

  @return Category bit
  */
  unsigned int getCategory(std::string category);
  /**
  @brief Get a mask bit from a name.

  @param category Category name

  @return Category mask
  */
  unsigned int getMask(std::string category);

private:
  /// @brief Categories
  std::map<std::string, unsigned int> _categories;
  /// @brief Masks
  std::map<std::string, unsigned int> _masks;

  /// @brief Current category
  unsigned int _currentCategory;

  /**
  @brief Add one mask for a category.

  @param name     Category
  @param category Other category
  */
  void addOneMask(std::string name, std::string category);
};

} /* physics2d */
} /* hx3d */

#include "hx3d/physics/2d/_inline/collision_matrix.inl.hpp"
