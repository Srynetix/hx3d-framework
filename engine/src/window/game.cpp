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
#include "hx3d/utils/string.hpp"

#include "hx3d/window/event_manager.hpp"
#include "hx3d/window/screen.hpp"

#include "hx3d/tweens/tween_manager.hpp"

#include "hx3d/graphics/text.hpp"
#include "hx3d/graphics/framebuffer.hpp"
#include "hx3d/graphics/viewports/viewport.hpp"
#include "hx3d/graphics/cameras/orthographic_camera.hpp"
#include "hx3d/graphics/transitions/transition.hpp"
#include "hx3d/graphics/batches/simple_batch.hpp"

namespace hx3d {
namespace window {

Game::Game():
_running(true), _screen(nullptr), _showStats(false)
{

  _deltaText = Make<graphics::Text>();
  _fpsText = Make<graphics::Text>();
  _camera = Make<graphics::OrthographicCamera>();
  _batch = Make<graphics::SimpleBatch>();
  _currentFB = Make<graphics::Framebuffer>();
  _nextFB = Make<graphics::Framebuffer>();

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
        // Remove old screen
        _screen->dispose();

        // Update screen
        _screen = _nextScreen;
        _nextScreen = nullptr;

        // Resume new screen
        _screen->resume();

        // Draw new screen
        _screen->render();

        _currentTransition->reset();
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
      // Remove old screen
      _screen->dispose();

      // Update screen
      _screen = _nextScreen;
      _nextScreen = nullptr;

      // Resume new screen
      _screen->resume();

      // Draw new screen
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
        // Update screens
        _screen->update(delta);
        _nextScreen->update(delta);

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

    // First screen ?
    if (!_screen) {
      _screen = screen;
      _screen->resume();

    } else {
      _nextScreen = screen;

      // Pause current screen (remove input)
      _screen->pause();
      // Pause next screen (remove input if taken)
      _nextScreen->pause();

      if (_currentTransition) {
        _currentTransition->start();
      }
    }

    // Resize new screen
    screen->resize(size.x, size.y);
  }
}

void Game::activateStats(bool enabled) {
  _showStats = enabled;
}

} /* window */
} /* hx3d */
