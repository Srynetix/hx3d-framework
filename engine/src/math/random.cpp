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

#include "hx3d/math/random.hpp"
#include "hx3d/utils/algorithm.hpp"
#include "hx3d/utils/log.hpp"

#include <cstdlib>

namespace hx3d {
namespace math {

WeightedRandom::WeightedRandom() {}

void WeightedRandom::define(int i, int weight, std::function<void()> f) {
  if (_weights.find(i) == _weights.end()) {
    _vec.push_back(i);
    _weights[i] = weight;
    _map[i] = f;
  } else {
    auto Log = Logger::getLogger("utils");
    Log.Error("WeightedRandom: Already defined '%d'", i);
  }
}

int WeightedRandom::random() {
  int n = get_number(math::random(0, total_count() - 1));
  _map[n]();

  return n;
}

int WeightedRandom::get_number(int gen) {
  int curr = 0;

  for (auto n: _vec) {
    for (int i = 0; i < _weights[n]; ++i) {
      if (gen == curr)
        return n;

      ++curr;
    }
  }

  return -1;
}

int WeightedRandom::total_count() {
  return algo::reduce(_vec, 0, [this](int res, int val){ return res + _weights[val]; });
}

///////////////////

float randfloat() {
  return (float)rand() / (RAND_MAX + 1.f);
}

bool flip_coin() {
  return random(0, 1) == 0;
}

} /* math */
} /* hx3d */
