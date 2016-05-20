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

#pragma once

#include "hx3d/utils/ptr.hpp"

/**
  @brief hx3d framework namespace
*/
namespace hx3d {

class AssetManager;
class Configuration;

namespace window {
  class Application;
  class Game;
  class EventManager;
}

namespace audio {
  class AudioDevice;
}

namespace net {
  class Net;
}

/**
@brief Centralized framework management.

Permit to manage assets, events and game management at one place.
*/
class Core {

public:

  /**
  @brief System types
  */
  enum class SystemType {
    /// @brief Android system
    Android,
    /// @brief iPhone/iPad system
    iOS,
    /// @brief Linux system
    Linux,
    /// @brief Windows system
    Windows,
    /// @brief MacOS system
    MacOS,
    /// @brief Unknown system
    Unknown
  };

  /**
  @brief Get the application instance

  @return Application
  */
  static window::Application* App();

  /**
  @brief Get the game instance

  @return Game
  */
  static Pointer<window::Game>& CurrentGame();

  /**
  @brief Get the asset manager.

  @return Asset manager
  */
  static Pointer<AssetManager>& Assets();

  /**
  @brief Get the event manager.

  @return Event manager
  */
  static Pointer<window::EventManager>& Events();

  /**
  @brief Get the net instance.

  @return Net
  */
  static Pointer<net::Net>& Network();

  /**
  @brief Get the audio device instance.

  @return Audio
  */
  static Pointer<audio::AudioDevice>& Audio();

  /**
  @brief Get the configuration instance.

  @return Config
  */
  static Pointer<Configuration>& Config();

  /**
  @brief Initialize the core system.

  @param app    Application (Ptr)
  */
  static void initialize(window::Application* app);

  /**
  @brief Set the game.

  @param game   Game (Ptr)
  */
  static void setGame(const Pointer<window::Game>& game);

  /**
  @brief Shutdown the core system.
  */
  static void shutdown();

  /// @brief Current system type
  static SystemType CurrentSystem;

  friend class Application;

private:
  Core();
  ~Core();

  /**
  Get the current core instance.

  @return Core instance.
  */
  static Core* get();

  /// @brief Core instance
  static Core* _instance;

  /// @brief Current application
  window::Application* _application;
  /// @brief Current game
  Pointer<window::Game> _game;
  /// @brief Current asset manager
  Pointer<AssetManager> _assets;
  /// @brief Current event manager
  Pointer<window::EventManager> _events;
  /// @brief Current net device
  Pointer<net::Net> _net;
  /// @brief Current audio device
  Pointer<audio::AudioDevice> _audio;
  /// @brief Configuration
  Pointer<Configuration> _config;
};

} /* hx3d */
