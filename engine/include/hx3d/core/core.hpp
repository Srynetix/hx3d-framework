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

#ifndef HX3D_CORE_CORE
#define HX3D_CORE_CORE

namespace hx3d {

class Application;
class Game;
class AssetManager;
class EventManager;

/**
Centralized framework management.
Permit to manage assets, events and game management at one place.
*/
class Core {

public:
  enum class SystemType {
    Android,
    iOS,
    Linux,
    Windows,
    MacOS,
    Unknown
  };

  /**
  Get the application instance
  @return Application
  */
  static Application* App();

  /**
  Get the game instance
  @return Game
  */
  static Game* CurrentGame();

  /**
  Get the asset manager.
  @return Asset manager
  */
  static AssetManager* Assets();

  /**
  Get the event manager.
  @return Event manager
  */
  static EventManager* Events();

  /**
  Set the current application.
  @param application Application (Ptr)
  */
  static void setApplication(Application* app);

  /**
  Set the current game.
  @param game Game (Ptr)
  */
  static void setGame(Game* game);

  /// Current system type
  static SystemType CurrentSystem;

private:
  Core();
  ~Core();

  /**
  Get the current core instance.
  @return Core instance.
  */
  static Core* get();

  static Core* _instance;

  static Application* _application;
  static Game* _game;
  static AssetManager* _assets;
  static EventManager* _events;
};

} /* hx3d */

#endif
