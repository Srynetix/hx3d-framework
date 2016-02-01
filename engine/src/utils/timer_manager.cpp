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
#include "hx3d/utils/log.hpp"

namespace hx3d {

TimerManager::TimerManager() {}

void TimerManager::addNamedTimer(std::string name, CallbackTimer& timer) {
  _registered[name] = timer;
}

void TimerManager::createNamedTimer(std::string name, float delay, std::function<void()> callback, bool loop) {
  _registered[name].initialize(delay, callback, loop);
}

void TimerManager::resetNamedTimer(std::string name) {
  _registered[name].reset();
}

void TimerManager::removeNamedTimer(std::string name) {
  if (_registered.find(name) != _registered.end()) {
    _registered.erase(name);
  }
}

void TimerManager::addTemporaryTimer(CallbackTimer& timer) {
  _temporaries.push_back(timer);
}

void TimerManager::createTemporaryTimer(float delay, std::function<void()> callback, bool loop) {
  CallbackTimer timer;
  timer.initialize(delay, callback, loop);

  _temporaries.push_back(timer);
}

void TimerManager::update(float delta) {
  std::vector<std::string> toRemoveReg;
  std::vector<int> toRemoveTemp;

  for (auto& pair: _registered) {
    auto& reg = pair.second;
    reg.update(delta);

    if (reg.hasEnded()) {
      toRemoveReg.push_back(pair.first);
    }
  }

  int i = 0;
  algo::apply(_temporaries, [&i,&toRemoveTemp,delta](CallbackTimer& reg) {
    reg.update(delta);
    if (reg.hasEnded()) {
      toRemoveTemp.push_back(i);
    }

    ++i;
  });

  while (!toRemoveReg.empty()) {
    _registered.erase(toRemoveReg.back());
  }

  while (!toRemoveTemp.empty()) {
    _temporaries.erase(_temporaries.begin() + toRemoveTemp.back());
  }
}

void TimerManager::clear() {
  _registered.clear();
  _temporaries.clear();
}

} /* hx3d */
