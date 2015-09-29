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

#include "hx3d/graphics/color.hpp"

namespace hx3d {
namespace math {

static float outBounce(float t) {
  return
    (t < 0.3636) ? 7.5625 * t * t:
    (t < 0.7272) ? 7.5625 * (t - 0.5454) * (t - 0.5454) + 0.75:
    (t < 0.9090) ? 7.5625 * (t - 0.8181) * (t - 0.8181) + 0.9375:
    7.5625 * (t - 0.9545) * (t - 0.9545) + 0.984375;
}

static float inExpo(float t) {
  return std::pow(2, 10 * (t-1));
}

static float inCirc(float t) {
  return -(std::sqrt(1 - t*t) - 1);
}

static float inBack(float t) {
  return t*t * (3*t - 2);
}

static float inElastic(float t) {
  return (t == 0 || t == 1) ? t :
    -std::pow(2, 8 * (t-1)) * std::sin(((t-1) * 80 - 7.5) * math::PI / 15);
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
      t = inExpo(t);
      break;
    case Interpolation::OutExpo:
      t = 1 - inExpo(1 - t);
      break;
    case Interpolation::InOutExpo:
      t = (t < 0.5f) ?
        inExpo(t * 2) / 2 :
        1 - inExpo(t * -2 + 2) / 2;
      break;

    case Interpolation::InCirc:
      t = inCirc(t);
      break;
    case Interpolation::OutCirc:
      t = 1 - inCirc(1 - t);
      break;
    case Interpolation::InOutCirc:
      t = (t < 0.5f) ?
        inCirc(t * 2) / 2 :
        1 - inCirc(t * -2 + 2) / 2;
      break;

    case Interpolation::InBack:
      t = inBack(t);
      break;
    case Interpolation::OutBack:
      t = 1 - inBack(1 - t);
      break;
    case Interpolation::InOutBack:
      t = (t < 0.5f) ?
        inBack(t * 2) / 2 :
        1 - inBack(t * -2 + 2) / 2;
      break;

    case Interpolation::InBounce:
      t = 1 - outBounce(1 - t);
      break;
    case Interpolation::OutBounce:
      t = outBounce(t);
      break;
    case Interpolation::InOutBounce:
      t =
        (t < 0.5f) ?
        (1 - outBounce(1 - t*2)) * 0.5:
        outBounce(t * 2 - 1) * 0.5 + 1 * 0.5;
      break;

    case Interpolation::InElastic:
      t = inElastic(t);
      break;
    case Interpolation::OutElastic:
      t = 1 - inElastic(1 - t);
      break;
    case Interpolation::InOutElastic:
      t = (t < 0.5f) ?
        inElastic(t * 2) / 2 :
        1 - inElastic(t * -2 + 2) / 2;
      break;

    case Interpolation::Linear:
    default:
      break;
  }

  return a + t*(b - a);
}

template <>
Color interpolate(Color a, Color b, float t, Interpolation type) {
  Color ca = Color::rgbToHsv(a);
  Color cb = Color::rgbToHsv(b);
  Color final;

  final.r = math::interpolate(ca.r, cb.r, t, type);
  final.g = math::interpolate(ca.g, cb.g, t, type);
  final.b = math::interpolate(ca.b, cb.b, t, type);

  return Color::hsvToRgb(final);
}

} /* math */
} /* hx3d */
