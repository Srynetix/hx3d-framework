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

/**
@mainpage hx3d Framework - Open Source & Easy to understand 2D/3D framework.

Welcome to the hx3d official documentation !

To go back to the **main page**, go to [srynetix.github.io](https://srynetix.github.io).\n
To go to the **tutorials**, click [here](https://srynetix.github.io/tutorials.html).
*/

#include "hx3d/core/core.hpp"
#include "hx3d/window/events.hpp"

#include "hx3d/net/net.hpp"
#include "hx3d/audio/audio.hpp"

#include "hx3d/utils/assets.hpp"

#include <cstdlib>

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
    Core::SystemType Core::CurrentSystem = Core::SystemType::MacOS;
  #endif
#else
  Core::SystemType Core::CurrentSystem = Core::SystemType::Unknown;
#endif

Core* Core::_instance(nullptr);

Core::Core() {
  _assets = new AssetManager();
  _net = new net::Net();
  _audio = new audio::AudioDevice();
}

Core::~Core() {
  if (_assets)
    delete _assets;
  if (_net)
    delete _net;
  if (_audio)
    delete _audio;
}

window::Application* Core::App() {
  return get()->_application;
}

window::Game* Core::CurrentGame() {
  return get()->_game;
}

AssetManager* Core::Assets() {
  return get()->_assets;
}

window::EventManager* Core::Events() {
  return get()->_events;
}

net::Net* Core::Network() {
  return get()->_net;
}

audio::AudioDevice* Core::Audio() {
  return get()->_audio;
}

/////////////////////////

void Core::initialize(window::Application* app, window::EventManager* events) {
  _instance = new Core();
  _instance->_application = app;
  _instance->_events = events;
}

void Core::setGame(window::Game* game) {
  _instance->_game = game;
}

void Core::shutdown() {
  if (_instance)
    delete _instance;
}

Core* Core::get() {
  if (!_instance) {
    Log.Error("Attempt to use the Core without initializing it.");
    exit(1);
  }

  return _instance;
}

} /* hx3d */
