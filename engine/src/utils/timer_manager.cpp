/*
    Timer manager.
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

#include "hx3d/utils/timer_manager.hpp"

#include "hx3d/utils/algorithm.hpp"

namespace hx3d {

TimerManager::TimerManager() {}

void TimerManager::addNamedTimer(std::string name, CallbackTimer& timer) {
  _registered[name] = timer;
}

void TimerManager::createNamedTimer(std::string name, float delay, std::function<void()> callback) {
  CallbackTimer timer;
  timer.initialize(delay, callback);

  _registered[name] = timer;
}

void TimerManager::addTemporaryTimer(CallbackTimer& timer) {
  _temporaries.push_back(timer);
}

void TimerManager::createTemporaryTimer(float delay, std::function<void()> callback) {
  CallbackTimer timer;
  timer.initialize(delay, callback);

  _temporaries.push_back(timer);
}

void TimerManager::update(float delta) {
  algo::apply(_registered, [delta](std::pair<std::string,CallbackTimer> pair) {
    auto& reg = pair.second;
    reg.update(delta);
  });

  algo::apply(_temporaries, [delta](CallbackTimer& reg) {
    reg.update(delta);
  });
}

} /* hx3d */
