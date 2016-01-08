/*
    SDL2 Application.
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

#ifndef HX3D_WINDOW_SDL2_SDL2APPLICATION
#define HX3D_WINDOW_SDL2_SDL2APPLICATION

#include "hx3d/window/application.hpp"

#include <SDL2/SDL.h>

namespace hx3d {
namespace window {

class Game;

/**
@brief SDL2 application implementation
*/
class SDL2Application: public Application {

public:
  /**
  @brief Create a SDL2 window.

  @param config Configuration
  */
  SDL2Application(ApplicationConfig config);
  virtual ~SDL2Application();

  virtual void start(const Ptr<Game>& game) override;

private:
  SDL_Window* _window;
  SDL_GLContext _context;

  /**
  @brief Create and initialize the window.

  @param width  Window width
  @param height Window height
  @param title  Window title
  */
  void create(int width, int height, std::string title);

  /**
  @brief Display the window and run the game loop.
  */
  void display();

  /**
  @brief Render the window to the screen.
  */
  void render();

  /**
  @brief Update the window content

  @param delta Delta time
  */
  void update(float delta);
};

} /* window */
} /* hx3d */

#endif /* HX3D_WINDOW_SDL2_SDL2APPLICATION */
