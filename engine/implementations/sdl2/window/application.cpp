/*
    SDL2 Application.
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

#include <SDL2/SDL.h>

#define HX3D_WINDOW_APPLICATION_INJECTION \
  SDL_Window* _window; \
  SDL_GLContext _context;

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/assets.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/framebuffer.hpp"
#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/font.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"
#include "hx3d/window/game.hpp"
#include "hx3d/window/events.hpp"
#include "hx3d/window/event_manager.hpp"

#include "hx3d/audio/audio.hpp"

#include "hx3d/math/number_utils.hpp"

#include "hx3d/net/net.hpp"

#include <ctime>

using namespace hx3d::graphics;

namespace hx3d {
namespace window {

Application::Application(ApplicationConfig config):
  _running(false),
  _width(config.width), _height(config.height), _fpsLimit(config.fpsLimit), _title(config.title),
  _fullscreen(config.fullscreen),
  _elapsedTime(0)
  {
    srand(time(0));

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
      Log.Error("SDL Init Error: %s", SDL_GetError());
      SDL_Quit();

      exit(1);
    }

    std::string hello =
    "\n\
                              *++++++!           +\n\
    ++|                      */      +           +\n\
      *            *    *            +          /+\n\
      * *****    *+/++++/+*    /++++*    +++++++!*\n\
      **/   !*       ++              +  /        |\n\
     +/+    +/+   +/++++/+   */      +  *        +\n\
     +/+    +/+  +/+    +/+   *+++++/    *++++++/\n";

    Log.Info(hello);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  #ifdef DESKTOP_OPENGL
    auto window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | (_fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, window_flags);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 0);
  #else
    _window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);

    SDL_GetWindowSize(_window, &_width, &_height);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  #endif

    _context = SDL_GL_CreateContext(_window);
    if (_context == 0) {
     Log.Error("OpenGL Context Error: %s", SDL_GetError());
     SDL_Quit();
    }

    SDL_GL_MakeCurrent(_window, _context);

   #ifdef DESKTOP_OPENGL
    GLenum init = glewInit();
    if (init != GLEW_OK) {
        Log.Error("GLEW error: %s", glewGetErrorString(init));
        exit(1);
    }
  #endif

    Log.Info("Screen: %d x %d", _width, _height);

    glViewport(0, 0, _width, _height);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Stencil bitplanes
    int bitplanes = 0;
    glGetIntegerv(GL_STENCIL_BITS, &bitplanes);

    Log.Info("Stencil bitplanes: %d", bitplanes);

    /** Initializations **/

    Core::initialize(this);
    Framebuffer::fetchDefaultFramebuffer();
    Texture::generateBlankTexture();

    Core::Assets()->create<Shader>("base", "shaders/base");
    Core::Assets()->create<Shader>("text", "shaders/text");
    Core::Assets()->create<Font>("default", "fonts/default.otf", 14);
  }

Application::~Application() {

  Core::shutdown();
  _game.reset();

  if (_window) {
    SDL_DestroyWindow(_window);
  }

  SDL_GL_DeleteContext(_context);
  SDL_Quit();

  Log.Info("> END");

  #if defined(__ANDROID__)
    exit(0);
  #endif

  /* Stop the static classes */
  //.........
}

void Application::start(const Ptr<Game>& game) {
  _game = game;

  Core::setGame(_game.get());
  _game->create();

  Uint32 frameTime = 0;
  Uint32 frameStart;
  Uint32 frameEnd;
  float deltaTime = 0.f;

  _running = true;
  while (_running) {

    frameStart = SDL_GetTicks();

    Core::Events()->poll();

    if (Core::Events()->isWindowState(WindowEvent::Type::Closed)) {
      _game->stop();
    } else {
      _game->update(deltaTime);
    }

    if (!_game->isRunning())
      _running = false;

    // Render !
    _game->render();

    SDL_GL_SwapWindow(_window);

    if (!_game->isRunning())
      _running = false;

    frameEnd = SDL_GetTicks();
    frameTime = frameEnd - frameStart;
    deltaTime = frameTime / 1000.f;

    _currentFPS = 1.f / deltaTime;
    _elapsedTime = math::mclamp(_elapsedTime + deltaTime, 0.f, 3600.f);
  }
}

} /* window */
} /* hx3d */
