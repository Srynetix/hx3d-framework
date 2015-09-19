/*
    Asset management.
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

#ifndef HX3D_UTILS_ASSETS
#define HX3D_UTILS_ASSETS

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/resource.hpp"
#include "hx3d/utils/log.hpp"

#include <typeindex>
#include <map>

namespace hx3d {

class AssetManager {

public:

  /**
  Create an asset with arguments.

  @param T    Asset type
  @param name Asset name
  @param args Arguments
  */
  template <class Asset, class... Args>
  void create(std::string name, Args... args);

  /**
  Add an asset.

  @param T      Asset type
  @param name   Asset name
  @param asset  Asset (Ptr)
  */
  template <class Asset>
  void add(std::string name, Ptr<Asset> asset);

  /**
  Get an asset.

  @param T      Asset type
  @param name   Asset name
  */
  template <class Asset>
  Ptr<Asset> get(std::string name);

private:
  std::map<std::type_index, std::map<std::string, Ptr<Resource>>> _assets;
};

#include "hx3d/utils/inline/assets.inl.hpp"

} /* hx3d */

#endif
