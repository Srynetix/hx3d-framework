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

template <class Asset, class... Args>
void AssetManager::create(std::string name, Args... args) {
  auto& type = typeid(Asset);
  if (_assets.find(type) == _assets.end()) {
    _assets[type] = std::map<std::string, Pointer<Resource>>();
  }

  _assets[type][name] = std::make_shared<Asset>(args...);
}

template <class Asset>
void AssetManager::add(std::string name, Pointer<Asset> asset) {
  auto& type = typeid(Asset);
  if (_assets.find(type) == _assets.end()) {
    _assets[type] = std::map<std::string, Pointer<Resource>>();
  }

  _assets[type][name] = asset;
}

template <class Asset>
Pointer<Asset> AssetManager::get(std::string name) {
  auto& type = typeid(Asset);
  if (_assets.find(type) == _assets.end()) {
    _assets[type] = std::map<std::string, Pointer<Resource>>();
  }

  if (_assets[type].find(name) == _assets[type].end()) {
    Log.Error("Asset `%s` unknown.", name.c_str());
    return nullptr;
  }

  return std::dynamic_pointer_cast<Asset>(_assets[type][name]);
}
