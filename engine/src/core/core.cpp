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

#include "hx3d/net/net.hpp"
#include "hx3d/audio/audio.hpp"

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
AssetManager* Core::_assets(nullptr);
EventManager* Core::_events(nullptr);
Net* Core::_net(nullptr);
Audio* Core::_audio(nullptr);

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

Net* Core::Network() {
  return get()->_net;
}

Audio* Core::AudioDevice() {
  return get()->_audio;
}

/////////////////////////

void Core::initialize(Application* app, Game* game) {
  _application = app;
  _game = game;

  _assets = new AssetManager();
  _events = new EventManager();
  _net = new Net();
  _audio = new Audio();

  _instance = new Core();
}

void Core::shutdown() {
  if (_assets)
    delete _assets;
  if (_events)
    delete _events;
  if (_net)
    delete _net;
  if (_audio)
    delete _audio;
}

Core* Core::get() {
  if (!_instance) {
    Log.Error("Attempt to use the Core without initializing it.");
    exit(1);
  }

  return _instance;
}

} /* hx3d */
