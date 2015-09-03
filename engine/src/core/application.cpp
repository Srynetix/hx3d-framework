/*
    Application management.
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

#include "hx3d/core/application.hpp"

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/assets.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/framebuffer.hpp"
#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/font.hpp"

#include "hx3d/core/game.hpp"
#include "hx3d/core/core.hpp"
#include "hx3d/core/events.hpp"

#include <ctime>

namespace hx3d {

Application::Application(Ptr<Game> game, ApplicationConfig config):
  _game(game), _running(true), _width(config.width), _height(config.height), _fpsLimit(config.fpsLimit), _elapsedTime(0)
{
  create(_width, _height, config.title);
}

Application::~Application() {

  SDL_GL_DeleteContext(_context);
  Log.Info("OpenGL context deleted.");

  if (_window) {
    SDL_DestroyWindow(_window);
    Log.Info("Window destroyed");
  }

  SDL_Quit();
  Log.Info("SDL shutdown.");
}

void Application::create(int width, int height, std::string title) {

  srand(time(0));

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    Log.Error("SDL Init Error: %s", SDL_GetError());
    SDL_Quit();

    exit(1);
  }

  Log.Info("SDL initialized.");

#ifdef DESKTOP_OPENGL
  _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  _width = width;
  _height = height;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 0);
#else
  _window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);

  SDL_GetWindowSize(_window, &_width, &_height);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
 #endif
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

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

  else {
    Log.Info("GLEW initialized.");
  }
#endif

  glViewport(0, 0, _width, _height);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Log.Info("OpenGL context created.");

  /** Initializations **/

  Core::setApplication(this);
  Framebuffer::fetchDefaultFramebuffer();
  Texture::generateBlankTexture();

  Core::Assets()->create<Shader>("base", "shaders/base");
  Core::Assets()->create<Shader>("text", "shaders/text");
  Core::Assets()->create<Font>("default", "fonts/default.otf", 14);

  /*********************/

  _game->create();

  display();
}

void Application::display() {

  Uint32 frameTime = 0;
  Uint32 frameStart;
  Uint32 frameEnd;

  unsigned int fpsMilli = 1000/_fpsLimit;

  while (_running) {

    frameStart = SDL_GetTicks();

    update();
    render();

    frameEnd = SDL_GetTicks();
    frameTime = frameEnd - frameStart;

    if (fpsMilli > frameTime) {
      SDL_Delay(fpsMilli - frameTime);
    }

    _currentFPS = 1.f / (frameTime / 1000.f);
    _elapsedTime += 1;
  }

}
void Application::update() {

  Core::Events()->poll();

  if (Core::Events()->isWindowState(WindowEvent::Type::Closed)) {
    _game->stop();
  } else {
    _game->update();
  }

  if (!_game->isRunning())
    _running = false;
}

void Application::render() {

  _game->render();

  SDL_GL_SwapWindow(_window);

  if (!_game->isRunning())
    _running = false;
}

int Application::getWidth() {
  return _width;
}

int Application::getHeight() {
  return _height;
}

glm::ivec2 Application::getSize() {
  return glm::ivec2(_width, _height);
}

float Application::getFPS() {
  return _currentFPS;
}

unsigned int Application::getElapsedTime() {
  return _elapsedTime;
}

} /* hx3d */
