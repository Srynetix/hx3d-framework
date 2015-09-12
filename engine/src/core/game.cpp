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

#include "hx3d/core/game.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/core/application.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {

  Game::Game():
  _running(true), _screen(nullptr)
  {}

  void Game::dispose() {
    if (_screen)
      _screen->hide();
  }

  void Game::pause() {
    if (_screen)
      _screen->pause();
  }

  void Game::resume() {
    if (_screen)
      _screen->resume();
  }

  void Game::render() {
    if (_screen)
      _screen->render();
  }

  void Game::update(float delta) {
    if (_screen)
      _screen->update(delta);
  }

  void Game::resize(int width, int height) {
    if (_screen)
      _screen->resize(width, height);
  }

  bool Game::isRunning() {
    return _running;
  }

  void Game::stop() {
    dispose();
    _running = false;
  }

  void Game::setScreen(Ptr<Screen> screen) {
    if (_screen)
      _screen->hide();

    _screen = screen;
    if (_screen) {
      _screen->show();
      _screen->resize(Core::App()->getWidth(), Core::App()->getHeight());
    }
  }

} /* hx3d */
