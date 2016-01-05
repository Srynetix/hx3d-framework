/*
    Application configuration.
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

#ifndef HX3D_WINDOW_APPLICATION_CONFIG
#define HX3D_WINDOW_APPLICATION_CONFIG

#include <string>

namespace hx3d {
namespace window {

/**
@brief Application configuration
*/
class ApplicationConfig {

public:
  /**
  @brief Default application config.

  Size: 1280 x 720
  Fullscreen: Off
  Title: Game
  FPS Limit: 60
  */
  ApplicationConfig();

  /// @brief FPS limit
  unsigned int fpsLimit;

  /// @brief Application width
  int width;
  /// @brief Application height
  int height;
  /// @brief Application title
  std::string title;
  /// @brief Is the application fullscreen ?
  bool fullscreen;
};

} /* window */
} /* hx3d */

#endif /* HX3D_WINDOW_APPLICATION_CONFIG */
