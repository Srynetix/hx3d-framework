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
#include "hx3d/utils/timer_manager.hpp"
#include "hx3d/tweens/tween_manager.hpp"
#include "hx3d/window/event_manager.hpp"

namespace hx3d {
namespace window {

Game::Game():
_running(true), _screen(nullptr), _showStats(false)
{
  _deltaText->transform.position.x = Core::App()->getWidth() / 2;
  _deltaText->transform.position.y = 100;
  _deltaText->transform.position.z = 0.95f;
  _deltaText->setCharacterSize(20);

  _fpsText->transform.position.x = Core::App()->getWidth() / 2;
  _fpsText->transform.position.y = _deltaText->transform.position.y + _deltaText->getCharacterSize();
  _fpsText->transform.position.z = 0.95f;
  _fpsText->setCharacterSize(20);

  _batch->setCamera(_camera);
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

void Game::setTransition(const Pointer<graphics::Transition>& transition) {
  _currentTransition = transition;
}

void Game::setViewport(const Pointer<graphics::Viewport>& viewport) {
  if (viewport) {
    auto world_size = viewport->getWorldSize();
    _currentFB->resize(world_size.x, world_size.y);
    _nextFB->resize(world_size.x, world_size.y);
  }

  _currentViewport = viewport;
  _currentViewport->apply(_camera);

  updateStats();
}

const Pointer<graphics::Viewport>& Game::getViewport() {
  return _currentViewport;
}

glm::vec2 Game::getSize() {
  if (_currentViewport)
    return _currentViewport->getWorldSize();
  else
    return Core::App()->getSize();
}

void Game::updateStats() {
  _deltaText->transform.position.x = this->getSize().x / 2;
  _deltaText->transform.position.y = 100;
  _deltaText->transform.position.z = 0.95f;
  _deltaText->setCharacterSize(20);

  _fpsText->transform.position.x = this->getSize().x / 2;
  _fpsText->transform.position.y = _deltaText->transform.position.y + _deltaText->getCharacterSize();
  _fpsText->transform.position.z = 0.95f;
  _fpsText->setCharacterSize(20);
}

void Game::render() {

  if (!_nextScreen) {
    if (_screen) {
      _screen->render();
    }
  }

  else {
    if (_currentTransition) {
      if (_currentTransition->isFinished()) {
        _screen->dispose();
        _screen = _nextScreen;
        _screen->resume();
        _currentTransition->reset();
        _nextScreen = nullptr;

        _screen->render();
      }

      else {
        graphics::Framebuffer::clear(graphics::Color::Black);

        graphics::Framebuffer::push(_currentFB);
        graphics::Framebuffer::clear(graphics::Color::Black);
        _screen->render();
        graphics::Framebuffer::pop();

        graphics::Framebuffer::push(_nextFB);
        graphics::Framebuffer::clear(graphics::Color::Black);
        _nextScreen->render();
        graphics::Framebuffer::pop();

        if (_currentViewport) _currentViewport->apply(_camera);
        _currentTransition->render(_batch, _currentFB, _nextFB);
      }
    }

    else {
      _screen->hide();
      _screen = _nextScreen;
      _screen->show();
      _nextScreen = nullptr;

      _screen->render();
    }
  }

  if (_showStats) {
    _batch->begin();
    _batch->draw(_deltaText);
    _batch->draw(_fpsText);
    _batch->end();
  }
}

ObjectMap& Game::getSession() {
  return _session;
}

void Game::update(float delta) {

  if (!_nextScreen) {
    _screen->update(delta);
  }

  else {
    if (_currentTransition) {
      if (_currentTransition->isRunning()) {
        _currentTransition->update(delta);
      }
    }
  }

  if (_showStats) {
    _deltaText->setContent(format("D: %2.0f", delta * 1000.f));
    _fpsText->setContent(format("FPS: %2.0f", 1/delta));
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

void Game::setScreen(const Pointer<Screen>& screen) {
  auto size = Core::App()->getSize();

  if (screen) {
    screen->show();
    screen->resize(size.x, size.y);

    if (!_screen) {
      _screen = screen;
    } else {
      _nextScreen = screen;
      _screen->hide();
      _nextScreen->pause();

      if (_currentTransition) {
        _currentTransition->start();
      }
    }
  }
}

void Game::activateStats(bool enabled) {
  _showStats = enabled;
}

} /* window */
} /* hx3d */
