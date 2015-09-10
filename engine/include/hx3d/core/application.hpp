/*
    Application management.
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

#ifndef HX3D_CORE_APPLICATION
#define HX3D_CORE_APPLICATION

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>

#include <string>

#include "hx3d/core/application_config.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Game;

/**
Application management
*/
class Application {

public:
  /**
  Create a window.

  @param game   Game instance (Ptr)
  @param config Configuration
  */
  Application(Ptr<Game> game, ApplicationConfig config);
  virtual ~Application();

  /**
  Get the window width

  @return Window width
  */
  int getWidth();

  /**
  Get the window height

  @return Window height
  */
  int getHeight();

  /**
  Get the window size (ivec2)

  @return Window size
  */
  glm::ivec2 getSize();

  /**
  Get the current frames per second (FPS)

  @return Current FPS
  */
  float getFPS();

  /*
  Get the elapsed time since the application start.
  
  @return Elapsed time
  */
  unsigned int getElapsedTime();

private:
  SDL_Window* _window;
  SDL_GLContext _context;
  Ptr<Game> _game;

  bool _running;

  int _width;
  int _height;

  float _currentFPS;
  unsigned int _fpsLimit;
  unsigned int _elapsedTime;

  /**
  Create and initialize the window.

  @param width  Window width
  @param height Window height
  @param title  Window title
  */
  void create(int width, int height, std::string title);

  /**
  Display the window and run the game loop.
  */
  void display();

  /**
  Render the window to the screen.
  */
  void render();

  /**
  Update the window content
  */
  void update();
};

} /* hx3d */

#endif
