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


    TODO
    > Screen transitions using framebuffers
*/

#ifndef HX3D_CORE_GAME
#define HX3D_CORE_GAME

#include "hx3d/core/application_listener.hpp"
#include "hx3d/core/screen.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Game: public ApplicationListener {
public:
  Game();

  virtual void render() override;
  virtual void update() override;
  virtual void resize(int width, int height) override;

  virtual void pause() override;
  virtual void resume() override;

  virtual void dispose() override;

  /**
  Set the current screen.
  @param screen Screen (Ptr)
  */
  void setScreen(Ptr<Screen> screen);

  /**
  Test if the game is running.
  */
  bool isRunning();

  /**
  Stop the game.
  */
  void stop();

private:
  bool _running;
  Ptr<Screen> _screen;
};

} /* hx3d */

#endif
