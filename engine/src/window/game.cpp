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

#include "hx3d/window/game.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"

#include "hx3d/utils/log.hpp"
#include "hx3d/window/event_manager.hpp"

namespace hx3d {
namespace window {

Game::Game():
_running(true), _screen(nullptr), _showStats(false)
{
  _deltaText.transform.position.x = Core::App()->getWidth() / 2;
  _deltaText.transform.position.y = 100;
  _deltaText.transform.position.z = 0.95f;
  _deltaText.setCharacterSize(20);

  _fpsText.transform.position.x = Core::App()->getWidth() / 2;
  _fpsText.transform.position.y = _deltaText.transform.position.y + _deltaText.getCharacterSize();
  _fpsText.transform.position.z = 0.95f;
  _fpsText.setCharacterSize(20);

  _batch.setCamera(_camera);
}

void Game::create() {}

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

  if (_showStats) {
    _batch.begin();
    _batch.draw(_deltaText);
    _batch.draw(_fpsText);
    _batch.end();
  }
}

void Game::update(float delta) {
  if (_screen)
    _screen->update(delta);

  if (_showStats) {
    _deltaText.setContent(format("D: %2.0f", delta * 1000.f));
    _fpsText.setContent(format("FPS: %2.0f", 1/delta));
  }
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

  Core::Events()->setInputHandler(nullptr);

  if (_screen)
    _screen->hide();

  _screen = screen;
  if (_screen) {
    _screen->show();
    _screen->resize(Core::App()->getWidth(), Core::App()->getHeight());
  }
}

void Game::activateStats(bool enabled) {
  _showStats = enabled;
}

} /* window */
} /* hx3d */
