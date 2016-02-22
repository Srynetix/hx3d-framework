/*
    Random functions.
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

#ifndef HX3D_MATH_RANDOM
#define HX3D_MATH_RANDOM

#include <functional>
#include <vector>
#include <map>

namespace hx3d {
namespace math {

/**
@brief Weighted random generator with callbacks.

<i>Example code</i>
@code
// Create a weighted random generator
math::WeightedRandom wr;

// Define the entry '0' with a weight of 5, will write "0 choosed !" if choosed.
wr.define(0, 5, [](){ Log.Info("0 choosed !") });

// Define the entry '1' with a weight of 2, will write "1 choosed !" if choosed.
wr.define(1, 2, [](){ Log.Info("1 choosed !") });

// Define the entry '2' with a weight of 8, will write "2 choosed !" if choosed.
wr.define(2, 8, [](){ Log.Info("2 choosed !") });

// Choose a number between the entries defined, execute the corresponding callback, and return the value choosed.
int choosed = wr.random(); // or only wr.random();
@endcode
*/
class WeightedRandom {
public:
  WeightedRandom();

  /**
  @brief Define a value with a weight and a callback.

  @param i      Value
  @param weight Weight
  @param f      Callback
  */
  void define(int i, int weight, std::function<void()> f);

  /**
  @brief Choose a random number and execute the callback

  @return Choosed value
  */
  int random();

private:
  std::vector<int> _vec;
  std::map<int, int> _weights;
  std::map<int, std::function<void()>> _map;

  int get_number(int gen);
  int total_count();
};

/**
@brief Generate a random float between 0.0 and 1.0.

@return Random float between 0.0 and 1.0
*/
float randfloat();

/**
@brief Generate a random integer between min and max.

@param min Min value
@param max Max value

@return Random integer between min and max.
*/
int random(int min, int max);

/**
@brief Return a random element.

@param vector Vector
*/
template <class T>
T random(std::vector<T>& vector);

/**
@brief Generate a random boolean.

@return Random boolean.
*/
bool flip_coin();

} /* math */
} /* hx3d */

#include "hx3d/math/_inline/random.inl.hpp"

#endif
