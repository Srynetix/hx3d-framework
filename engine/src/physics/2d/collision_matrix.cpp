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

#include "hx3d/physics/2d/collision_matrix.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace physics2d {

CollisionMatrix::CollisionMatrix() {
  _currentCategory = 0x1;
}

void CollisionMatrix::addCategory(std::string name) {
  if (_categories.find(name) != _categories.end()) {
    Log.Error("Physics2D: Category `%s` already exists !", name.c_str());
    return;
  }

  _categories[name] = _currentCategory;
  _masks[name] = 0x0;
  _currentCategory <<= 0x1;
}

void CollisionMatrix::addOneMask(std::string name, std::string category) {
  if (_categories.find(name) == _categories.end()) {
    Log.Error("Physics2D: Category `%s` does not exists !", name.c_str());
    return;
  }

  if (_categories.find(category) == _categories.end()) {
    Log.Error("Physics2D: Category `%s` does not exists !", category.c_str());
    return;
  }

  unsigned int mask = _masks[name];
  unsigned int cat = _categories[name];
  unsigned int otherCategory = _categories[category];
  unsigned int otherMask = _masks[category];

  mask |= otherCategory;
  otherMask |= cat;

  _masks[name] = mask;
  _masks[category] = otherMask;
}

unsigned int CollisionMatrix::getCategory(std::string category) {
  if (_categories.find(category) == _categories.end()) {
    Log.Error("Physics2D: Category `%s` does not exists !", category.c_str());
    return 0;
  }

  return _categories[category];
}

unsigned int CollisionMatrix::getMask(std::string category) {
  if (_categories.find(category) == _categories.end()) {
    Log.Error("Physics2D: Category `%s` does not exists !", category.c_str());
    return 0;
  }

  return _masks[category];
}

} /* physics2d */
} /* hx3d */
