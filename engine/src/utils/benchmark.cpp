/*
    Benchmark utils.
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

#include "hx3d/utils/benchmark.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {

Benchmark::Measure::Measure(std::string name, std::function<void()> fn): name(name), fn(fn) {}

///////////

Benchmark::Benchmark() {}

void Benchmark::bench(std::string name, std::function<void()> fn) {
  auto begin = std::chrono::system_clock::now();
  fn();
  auto end = std::chrono::system_clock::now();

  showStats(name, begin, end);
}

////////////

void Benchmark::showStats(std::string name, std::chrono::time_point<std::chrono::system_clock> begin, std::chrono::time_point<std::chrono::system_clock> end) {

  auto Log = Logger::getLogger("utils");

  float s = 0;
  int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
  if (ms == 0) {
    s = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000000000.f;
  } else {
    s = ms / 1000.f;
  }

  Log.Info("-- Bench '%s'\n\t -- %.8f sec.", name.c_str(), s);
}

} /* hx3d */
