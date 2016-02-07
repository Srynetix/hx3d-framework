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

#ifndef HX3D_UTILS_BENCHMARK
#define HX3D_UTILS_BENCHMARK

#include <functional>
#include <chrono>

namespace hx3d {

/**
@brief Benchmark helper.

<i>Example code</i>
@code
// Prepare the benchmark
Benchmark bm;

// Bench one test: Create a 1000000-int array
bm.bench("Test One", [](){
  int* tab = new int[1000000];
  delete[] tab;
});

[...]

// Bench multiple tests
bm.multiBench(
  Benchmark::Measure("One", [](){
    Log.Info("One !");
  }),
  Benchmark::Measure("Two", [](){
    Log.Info("Two !");
  })
);
@endcode
*/
class Benchmark {
public:

  /**
  @brief Benchmark measure
  */
  struct Measure {
    /// @brief Measure name
    std::string name;
    /// @brief Function
    std::function<void()> fn;

    Measure(std::string name, std::function<void()> fn);
  };

  Benchmark();

  /**
  @brief Measure one function.

  @param name Measure name
  @param fn   Function
  */
  void bench(std::string name, std::function<void()> fn);

  /**
  @brief Measure multiple functions.

  @param measure  Measure
  @param measures Other measures
  */
  template <class... Measures>
  void multiBench(Measure measure, Measures... measures);
  template <class... Measures>
  void multiBench(typename std::enable_if<sizeof...(Measures) == 0>::type* test = nullptr);

private:
  /**
  @brief Display measure stats.

  @param name   Name
  @param begin  Begin point
  @param end    End point
  */
  void showStats(std::string name, std::chrono::time_point<std::chrono::system_clock> begin, std::chrono::time_point<std::chrono::system_clock> end);
};

} /* hx3d */

#include "hx3d/utils/_inline/benchmark.inl.hpp"

#endif /* HX3D_UTILS_BENCHMARK */
