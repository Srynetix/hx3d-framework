/*
    Pool system.
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

#ifndef HX3D_UTILS_POOL
#define HX3D_UTILS_POOL

#include "hx3d/utils/ptr.hpp"

#include <set>
#include <queue>

namespace hx3d {

/**
@brief Manage poolable elements.
*/
template <class T>
class Pool {
public:

  /**
  @brief Construct a pool with a size and arguments.

  @param size Size
  @param args Arguments
  */
  template <class... Args>
  Pool(unsigned int size, Args... args);
  ~Pool();

  /**
  @brief Fetch a free poolable element.

  @return Poolable element
  */
  const Ptr<T>& take();

  /**
  @brief Release a poolable element.

  @param ptr Poolable (Ptr)
  */
  void release(const Ptr<T>& ptr);

  /**
  @brief Get the locked elements.

  @return Set of elements
  */
  const std::set<Ptr<T>>& getWorking();

private:
  std::queue<unsigned int> _available;
  std::set<unsigned int> _locked;

  std::set<Ptr<T>> _working;
  std::vector<Ptr<T>> _content;

  unsigned int size;

};

} /* hx3d */

#include "hx3d/utils/_inline/pool.inl.hpp"

#endif
