/*
    SDL2 Events Implementation.
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

#include "hx3d/window/impl/sdl2/event_manager.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"
#include "hx3d/window/input_handler.hpp"

#include <SDL2/SDL_events.h>

namespace hx3d {
namespace window {

void EventManager::beginTextInput() {
  _textInputMode = true;
  SDL_StartTextInput();
}

void EventManager::endTextInput() {
  _textInputMode = false;
  SDL_StopTextInput();
}

void EventManager::poll() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_WINDOWEVENT) {
      WindowEvent::Type type(WindowEvent::Type::None);

      switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
          type = WindowEvent::Type::Closed;
          break;
        case SDL_WINDOWEVENT_SHOWN:
          type = WindowEvent::Type::Shown;
          break;
        case SDL_WINDOWEVENT_MOVED:
          type = WindowEvent::Type::Moved;
          break;
      }

      _windowEvents[static_cast<unsigned int>(type)] = true;
      if (_currentHandler) {
        _currentHandler->onWindowEvent(type);
      }
    }

    else if (event.type == SDL_TEXTINPUT) {
      _currentWrittenText = event.text.text;
      if (_currentHandler) {
        _currentHandler->onTextInput(_currentWrittenText);
      }
    }

    else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
      MouseButtonEvent::Type type(event.type == SDL_MOUSEBUTTONDOWN ? MouseButtonEvent::Type::Clicked : MouseButtonEvent::Type::Released);
      MouseButtonEvent::Button key(MouseButtonEvent::Button::None);

      switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          key = MouseButtonEvent::Button::Left;
          break;
        case SDL_BUTTON_RIGHT:
          key = MouseButtonEvent::Button::Right;
          break;
        case SDL_BUTTON_MIDDLE:
          key = MouseButtonEvent::Button::Middle;
          break;
        case SDL_BUTTON_X1:
          key = MouseButtonEvent::Button::Special1;
          break;
        case SDL_BUTTON_X2:
          key = MouseButtonEvent::Button::Special2;
          break;
      }

      _mousePosition = glm::vec2(event.button.x, event.button.y);

      unsigned int position = static_cast<unsigned int>(key);
      if (type == MouseButtonEvent::Type::Released) {
        _mouseButtonReleased[position] = true;
        _mouseButtonClicked[position] = false;

        if (_currentHandler) {
          _currentHandler->onMouseReleased(key, _mousePosition);
        }

      } else {
        _mouseButtonClicked[position] = true;
        _mouseButtonReleased[position] = false;

        if (_currentHandler) {
          _currentHandler->onMouseClicked(key, _mousePosition);
        }
      }

      if (_touchSimulation) {
        _touchPosition = glm::vec2(_mousePosition.x / Core::App()->getWidth(),
        _mousePosition.y / Core::App()->getHeight());
        _touchMovement = glm::vec2(0);
        _touchPressure = 1.f;

        if (type == MouseButtonEvent::Type::Released) {
          _screenTouched = false;
          _screenReleased = true;

          if (_currentHandler) {
            _currentHandler->onTouchUp(_touchPosition, _touchPressure);
          }

        } else {
          _screenReleased = false;
          _screenTouched = true;

          if (_currentHandler) {
            _currentHandler->onTouchDown(_touchPosition, _touchPressure);
          }
        }
      }
    }

    else if (event.type == SDL_MOUSEMOTION) {
      _mousePosition = glm::vec2(event.motion.x, event.motion.y);
      _mouseMovement = glm::vec2(event.motion.xrel, event.motion.yrel);

      if (_currentHandler) {
        _currentHandler->onMouseMotion(_mousePosition, _mouseMovement);
      }

      if (_touchSimulation) {
        _touchPosition = _mousePosition;
        _touchMovement = _mouseMovement;

        if (_currentHandler) {
          _currentHandler->onTouchMotion(_touchPosition, _touchMovement, _touchPressure);
        }
      }
    }

    else if (event.type == SDL_MOUSEWHEEL) {
      MouseWheelEvent::Direction direction(MouseWheelEvent::Direction::None);

      if (event.wheel.x > 0)
        direction = MouseWheelEvent::Direction::Left;
      else if (event.wheel.x < 0)
        direction = MouseWheelEvent::Direction::Right;
      else if (event.wheel.y > 0)
        direction = MouseWheelEvent::Direction::Up;
      else if (event.wheel.y < 0)
        direction = MouseWheelEvent::Direction::Down;

      unsigned int position = static_cast<unsigned int>(direction);
      _mouseWheelTurned[position] = true;

      _mouseWheelMovement = glm::vec2(event.wheel.x, event.wheel.y);

      if (_currentHandler) {
        _currentHandler->onMouseWheel(direction, _mouseWheelMovement);
      }
    }

    else if (event.type == SDL_FINGERUP || event.type == SDL_FINGERDOWN) {
      TouchEvent::Type type(event.type == SDL_FINGERDOWN ? TouchEvent::Type::Touched : TouchEvent::Type::Released);

      _touchPosition = glm::vec2(event.tfinger.x, event.tfinger.y);
      _touchPressure = event.tfinger.pressure;

      if (type == TouchEvent::Type::Released) {

        if (_screenReleased)
          return;

        _touchMovement = glm::vec2(0);

        _screenTouched = false;
        _screenReleased = true;

        if (_currentHandler) {
          _currentHandler->onTouchUp(_touchPosition, _touchPressure);
        }

      } else {

        if (_screenTouched)
          return;

        _touchMovement = glm::vec2(0);

        _screenReleased = false;
        _screenTouched = true;

        if (_currentHandler) {
          _currentHandler->onTouchDown(_touchPosition, _touchPressure);
        }
      }
    }

    else if (event.type == SDL_FINGERMOTION) {
      _touchPosition = glm::vec2(event.tfinger.x, event.tfinger.y);
      _touchMovement = glm::vec2(event.tfinger.dx, event.tfinger.dy) * 300.f;

      _touchPressure = event.tfinger.pressure;

      if (_currentHandler) {
        _currentHandler->onTouchMotion(_touchPosition, _touchMovement, _touchPressure);
      }
    }

    else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      KeyEvent::Type type(event.type == SDL_KEYDOWN ? KeyEvent::Type::Pressed : KeyEvent::Type::Released);
      KeyEvent::Key key(KeyEvent::Key::None);

      if (event.key.repeat) {
        continue;
      }

      switch (event.key.keysym.sym) {
        case SDLK_a:
          key = KeyEvent::Key::A;
          break;
        case SDLK_b:
          key = KeyEvent::Key::B;
          break;
        case SDLK_c:
          key = KeyEvent::Key::C;
          break;
        case SDLK_d:
          key = KeyEvent::Key::D;
          break;
        case SDLK_e:
          key = KeyEvent::Key::E;
          break;
        case SDLK_q:
          key = KeyEvent::Key::Q;
          break;
        case SDLK_s:
          key = KeyEvent::Key::S;
          break;
        case SDLK_z:
          key = KeyEvent::Key::Z;
          break;
        case SDLK_UP:
          key = KeyEvent::Key::Up;
          break;
        case SDLK_DOWN:
          key = KeyEvent::Key::Down;
          break;
        case SDLK_LEFT:
          key = KeyEvent::Key::Left;
          break;
        case SDLK_RIGHT:
          key = KeyEvent::Key::Right;
          break;
        case SDLK_SPACE:
          key = KeyEvent::Key::Space;
          break;
        case SDLK_ESCAPE:
          key = KeyEvent::Key::Escape;
          break;
        case SDLK_RETURN:
          key = KeyEvent::Key::Return;
          break;
        case SDLK_AC_BACK:
          key = KeyEvent::Key::AndroidBack;
          break;
        case SDLK_MENU:
          key = KeyEvent::Key::AndroidMenu;
          break;
        case SDLK_BACKSPACE:
          key = KeyEvent::Key::Backspace;
          break;
        case 178:
          key = KeyEvent::Key::ConsoleKey;
        default:
          break;
      }

      unsigned int position = static_cast<unsigned int>(key);

      if (type == KeyEvent::Type::Released) {
        _keysReleased[position] = true;
        _keysPressed[position] = false;

        if (_currentHandler) {
          _currentHandler->onKeyReleased(key);
        }

      } else {
        _keysPressed[position] = true;
        _keysReleased[position] = false;

        if (_currentHandler) {
          _currentHandler->onKeyPressed(key);
        }
      }
    }
  }
}

} /* window */
} /* hx3d */
