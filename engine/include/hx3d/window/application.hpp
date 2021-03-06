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

/**
@brief Windowing and event components
*/
namespace window {

class Game;

/**
@brief Application management
*/
class Application {

public:
  /**
  @brief Create a window.

  @param config Configuration
  */
  Application(ApplicationConfig config);
  virtual ~Application();

  /**
  @brief Start the window.

  @param game   Game (Ptr)
  */
  virtual void start(const Ptr<Game>& game) = 0;

  /**
  @brief Get the window width

  @return Window width
  */
  int getWidth();

  /**
  @brief Get the window height

  @return Window height
  */
  int getHeight();

  /**
  @brief Get the window size (ivec2)

  @return Window size
  */
  glm::ivec2 getSize();

  /**
  @brief Get the current frames per second (FPS)

  @return Current FPS
  */
  float getFPS();

  /**
  @brief Get the elapsed time in seconds since the application start.
  Reset after one hour.

  @return Elapsed time
  */
  float getElapsedTime();

protected:

  /// @brief Game pointer
  Ptr<Game> _game;
  /// @brief Is the application running ?
  bool _running;

  /// @brief Application width
  int _width;
  /// @brief Application height
  int _height;
  /// @brief FPS limit
  unsigned int _fpsLimit;
  /// @brief Application title
  std::string _title;
  /// @brief Is the application in fullscreen ?
  bool _fullscreen;

  /// @brief Current FPS
  float _currentFPS;
  /// @brief Elapsed time since the beginning
  float _elapsedTime;
};

} /* window */
} /* hx3d */

#endif /* HX3D_WINDOW_APPLICATION */
