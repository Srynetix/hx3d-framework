/*
    Centralized framework management.
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

#include "hx3d/core/core.hpp"

#include "hx3d/core/events.hpp"

#include "hx3d/utils/assets.hpp"

namespace hx3d {

#if __ANDROID__
  Core::SystemType Core::CurrentSystem = Core::SystemType::Android;
#elif __unix
  Core::SystemType Core::CurrentSystem = Core::SystemType::Linux;
#elif _WIN32_
  Core::SystemType Core::CurrentSystem = Core::SystemType::Windows;
#elif __APPLE__
  #include "TargetConditionals.h"
  #if TARGET_IPHONE_SIMULATOR
    Core::SystemType Core::CurrentSystem = Core::SystemType::iOS;
  #elif TARGET_OS_IPHONE
    Core::SystemType Core::CurrentSystem = Core::SystemType::iOS;
  #elif TARGET_OS_MAC
    Core::SystemType Core::CurrentSystem = Core::SystemType::MacOSX;
  #endif
#else
  Core::SystemType Core::CurrentSystem = Core::SystemType::Unknown;
#endif

Core* Core::_instance(nullptr);
Application* Core::_application(nullptr);
Game* Core::_game(nullptr);
AssetManager* Core::_assets(new AssetManager());
EventManager* Core::_events(new EventManager());

Core::Core() {}
Core::~Core() {}

Application* Core::App() {
  return get()->_application;
}

Game* Core::CurrentGame() {
  return get()->_game;
}

AssetManager* Core::Assets() {
  return get()->_assets;
}

EventManager* Core::Events() {
  return get()->_events;
}

void Core::setApplication(Application* app) {
  _application = app;
}

void Core::setGame(Game* game) {
  _game = game;
}

/////////////////////////

Core* Core::get() {
  if (_instance == nullptr)
    _instance = new Core();

  return _instance;
}

} /* hx3d */
