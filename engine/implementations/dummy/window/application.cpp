/*
    Dummy Application Implementation.
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

#define HX3D_WINDOW_APPLICATION_INJECTION \
    std::string _hello;

#include "hx3d/window/application.hpp"
#include "hx3d/window/game.hpp"

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace window {

Application::Application(ApplicationConfig config): _hello("Coucou") {
  Log.Info("I will crash and it's perfectly normal (because I don't initialize Core)");
  Log.Info("Hello: %s", _hello.c_str());
}

Application::~Application() {}

void Application::start(const Ptr<Game>& game) {}

} /* window */
} /* hx3d */
