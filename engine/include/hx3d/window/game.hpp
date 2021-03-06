/*
    Game management.
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

#ifndef HX3D_WINDOW_GAME
#define HX3D_WINDOW_GAME

#include "hx3d/window/screen.hpp"
#include "hx3d/gui/text.hpp"
#include "hx3d/graphics/cameras/orthographic_camera.hpp"
#include "hx3d/graphics/batch.hpp"
#include "hx3d/graphics/framebuffer.hpp"
#include "hx3d/graphics/viewports/viewport.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/transition.hpp"

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/object_map.hpp"

namespace hx3d {
namespace window {

/**
@brief Game main class: multiple screens management
*/
class Game {
public:
  Game();

  /**
  @brief Initialize the game
  */
  virtual void create();

  /**
  @brief Render the current scren
  */
  virtual void render();

  /**
  @brief Update the current screen

  @param delta Delta time
  */
  virtual void update(float delta);

  /**
  @brief Resize the current screen

  @param width  New width
  @param height New height
  */
  virtual void resize(int width, int height);

  /**
  @brief Pause the current screen
  */
  virtual void pause();

  /**
  @brief Resume the current screen
  */
  virtual void resume();

  /**
  @brief Clean the current screen
  */
  virtual void dispose();

  /**
  @brief Stop the game.
  */
  virtual void stop();

  /**
  @brief Set the current screen.

  @param screen Screen (Ptr)
  */
  void setScreen(Ptr<Screen> screen);

  /**
  @brief Activate the stats.

  @param enabled True/False
  */
  void activateStats(bool enabled);

  /**
  @brief Set the current transition.

  @param transition Transition
  */
  void setTransition(const Ptr<graphics::Transition>& transition);

  /**
  @brief Set the current viewport

  @param viewport Viewport
  */
  void setViewport(const Ptr<graphics::viewports::Viewport>& viewport);

  /**
  @brief Get the current viewport

  @return Viewport
  */
  const Ptr<graphics::viewports::Viewport>& getViewport();

  /**
  @brief Get the session

  @return Session
  */
  ObjectMap& getSession();

  /**
  @brief Get the current game size.

  If a viewport is enabled, return the viewport size.
  Else, return the application size.

  @return Game size
  */
  glm::vec2 getSize();

  /**
  @brief Test if the game is running.

  @return True/False
  */
  bool isRunning();

private:
  bool _running;
  Ptr<Screen> _screen;
  Ptr<Screen> _nextScreen;
  gui::Text _deltaText;
  gui::Text _fpsText;

  graphics::OrthographicCamera _camera;
  graphics::Batch _batch;

  graphics::Framebuffer _currentFB;
  graphics::Framebuffer _nextFB;
  Ptr<graphics::Transition> _currentTransition;
  Ptr<graphics::viewports::Viewport> _currentViewport;

  ObjectMap _session;

  bool _showStats;

  void updateStats();
};

} /* window */
} /* hx3d */

#endif /* HX3D_WINDOW_GAME */
