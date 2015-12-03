/*
    Application management interface.
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

#ifndef HX3D_WINDOW_APPLICATION
#define HX3D_WINDOW_APPLICATION

#include "hx3d/window/application_config.hpp"
#include "hx3d/utils/ptr.hpp"

#include <string>
#include <glm/vec2.hpp>

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
  Application(const Ptr<Game>& game, ApplicationConfig config);
  virtual ~Application();

  /**
  Start the window.
  */
  virtual void start() = 0;

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
  Get the elapsed time in seconds since the application start.
  Reset after one hour.

  @return Elapsed time
  */
  float getElapsedTime();

protected:
    Ptr<Game> _game;
    bool _running;

    int _width;
    int _height;
    unsigned int _fpsLimit;
    std::string _title;

    float _currentFPS;
    float _elapsedTime;
};

} /* hx3d */

#endif /* HX3D_WINDOW_APPLICATION */
