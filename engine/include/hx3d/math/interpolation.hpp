/*
    Interpolation functions.
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

#ifndef HX3D_MATH_INTERPOLATION
#define HX3D_MATH_INTERPOLATION

#include <glm/vec2.hpp>
#include <functional>

#include "hx3d/math/constants.hpp"

namespace hx3d {
namespace math {

enum class Interpolation {
  Linear = 0,

  InQuad,
  OutQuad,
  InOutQuad,

  InCubic,
  OutCubic,
  InOutCubic,

  InQuart,
  OutQuart,
  InOutQuart,

  InQuint,
  OutQuint,
  InOutQuint,

  InSine,
  OutSine,
  InOutSine,

  InExpo,
  OutExpo,
  InOutExpo,

  InCirc,
  OutCirc,
  InOutCirc,

  InBack,
  OutBack,
  InOutBack,

  InBounce,
  OutBounce,
  InOutBounce,

  InElastic,
  OutElastic,
  InOutElastic
};

static float outBounce(float t) {
  return
    (t < 0.3636) ? 7.5625 * t * t:
    (t < 0.7272) ? 7.5625 * (t - 0.5454) * (t - 0.5454) + 0.75:
    (t < 0.9090) ? 7.5625 * (t - 0.8181) * (t - 0.8181) + 0.9375:
    7.5625 * (t - 0.9545) * (t - 0.9545) + 0.984375;
}

template <class T>
T interpolate(T a, T b, float t, Interpolation type) {
  switch (type) {
      break;
    case Interpolation::InQuad:
      t = t * t;
      break;
    case Interpolation::OutQuad:
      t = t * (2-t);
      break;
    case Interpolation::InOutQuad:
      t = (t < 0.5f) ? 2 * t * t : -1 + (4-2*t)*t;
      break;

    case Interpolation::InCubic:
      t = t * t * t;
      break;
    case Interpolation::OutCubic:
      t = (t-1) * (t-1) * (t-1) + 1;
      break;
    case Interpolation::InOutCubic:
      t = (t < 0.5f) ? 4*t*t*t : (t-1)*(2*t-2)*(2*t-2)+1;
      break;

    case Interpolation::InQuart:
      t = t * t * t * t;
      break;
    case Interpolation::OutQuart:
      t = 1 - (t-1) * (t-1) * (t-1) * (t-1);
      break;
    case Interpolation::InOutQuart:
      t = (t < 0.5f) ? 8*t*t*t*t : 1 - 8*(t-1)*(t-1)*(t-1)*(t-1);
      break;

    case Interpolation::InQuint:
      t = t*t*t*t*t*t;
      break;
    case Interpolation::OutQuint:
      t = 1 + (t-1) * (t-1) * (t-1) * (t-1) * (t-1);
      break;
    case Interpolation::InOutQuint:
      t = (t < 0.5f) ? 16*t*t*t*t*t : 1 + 16*(t-1)*(t-1)*(t-1)*(t-1)*(t-1);
      break;

    case Interpolation::InSine:
      t = -1 * std::cos(t * (math::PI / 2)) + 1;
      break;
    case Interpolation::OutSine:
      t = std::sin(t * (math::PI / 2));
      break;
    case Interpolation::InOutSine:
      t = (std::cos(t * math::PI) - 1) / -2;
      break;

    case Interpolation::InExpo:
      t = std::pow(2, 10 * (t-1));
      break;
    case Interpolation::OutExpo:
      t = -std::pow(2, -10 * t) + 1;
      break;
    case Interpolation::InOutExpo:
      /* BROKEN */
      t = t/2;
      t = (std::pow(2, 10 * (t-1))) / 2;
      break;

    case Interpolation::InCirc:
      t = -1 * (std::sqrt(1 - t*t) - 1);
      break;
    case Interpolation::OutCirc:
      t = std::sqrt(1 - (t - 1) * (t - 1));
      break;
    case Interpolation::InOutCirc:
      /* BROKEN */
      t = t/2;
      t = (std::sqrt(1 - t*t) - 1) / -2;
      break;

    case Interpolation::InBack:
      {
        float overshoot = 1.70158;
        t = 1 * t*t*((overshoot + 1) * t - overshoot);
      }
      break;
    case Interpolation::OutBack:
      {
        float overshoot = 1.70158;
        t = t - 1;
        t = t * t * ((overshoot + 1) * t + overshoot) + 1;
      }
      break;
    case Interpolation::InOutBack:
      /* BROKEN */
      {
        float overshoot = 1.70158;
        t = t/2;
        overshoot = overshoot * 1.525;
        t = (t * t * ((overshoot + 1) * t - overshoot)) / 2;
      }
      break;

    case Interpolation::InBounce:
      t = 1 - outBounce(1 - t);
      break;
    case Interpolation::OutBounce:
      t = outBounce(t);
      break;
    case Interpolation::InOutBounce:
      t =
        (t < 0.5f) ? (1 - outBounce(1 - t*2)) * 0.5:
        outBounce(t * 2 - 1) * 0.5 + 1 * 0.5;
      break;

    case Interpolation::InElastic:
      {
        float amplitude = 1.f;
        float period = 0.3f;
        float offset = period / 4;

        if (t == 0 || t == 1)
          break;

        t = t - 1;
        t = -(amplitude * std::pow(2, 10 * t) * std::sin(((t - offset) * (math::PI * 2)) / period));
      }
      break;
    case Interpolation::OutElastic:
      {
        float amplitude = 1.f;
        float period = 0.3f;
        float offset = period / 4;

        if (t == 0 || t == 1)
          break;

        t = amplitude * std::pow(2, -10 * t) * std::sin((t - offset) * (math::PI * 2) / period) + 1;
      }
      break;
    case Interpolation::InOutElastic:
      /* BROKEN */
      {
        float amplitude = 1.f;
        float period = 0.4499f;
        float offset = period / 4;

        if (t == 0 || t == 1)
          break;

        t = (amplitude * std::pow(2, 10*t) * std::sin((t - offset) * (math::PI * 2) / period)) / -2;
      }
      break;

    case Interpolation::Linear:
    default:
      break;
  }

  return a + t*(b - a);
}

} /* math */
} /* hx3d */

#endif
