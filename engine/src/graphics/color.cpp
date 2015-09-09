/*
    Color.
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

Color::Color():
  r(255), g(255), b(255), a(255) {}
Color::Color(unsigned char r, unsigned char g, unsigned char b):
  r(r), g(g), b(b), a(255) {}
Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a):
  r(r), g(g), b(b), a(a) {}

Color& Color::operator=(const Color& color) {
  r = color.r;
  g = color.g;
  b = color.b;
  a = color.a;

  return *this;
}

glm::vec4 Color::toFloat() {
  return glm::vec4(r/255.f, g/255.f, b/255.f, a/255.f);
}

Color Color::hsvToRgb(Color hsv)
{
  Color rgb;
  unsigned char region, remainder, p, q, t;

  if (hsv.g == 0)
  {
      rgb.r = hsv.r;
      rgb.g = hsv.g;
      rgb.b = hsv.b;
      return rgb;
  }

  region = hsv.r / 43;
  remainder = (hsv.r - (region * 43)) * 6;

  p = (hsv.b * (255 - hsv.g)) >> 8;
  q = (hsv.b * (255 - ((hsv.g * remainder) >> 8))) >> 8;
  t = (hsv.b * (255 - ((hsv.g * (255 - remainder)) >> 8))) >> 8;

  switch (region)
  {
      case 0:
          rgb.r = hsv.b; rgb.g = t; rgb.b = p;
          break;
      case 1:
          rgb.r = q; rgb.g = hsv.b; rgb.b = p;
          break;
      case 2:
          rgb.r = p; rgb.g = hsv.b; rgb.b = t;
          break;
      case 3:
          rgb.r = p; rgb.g = q; rgb.b = hsv.b;
          break;
      case 4:
          rgb.r = t; rgb.g = p; rgb.b = hsv.b;
          break;
      default:
          rgb.r = hsv.b; rgb.g = p; rgb.b = q;
          break;
  }

  return rgb;
}

Color Color::rgbToHsv(Color rgb)
{
    Color hsv;
    unsigned char rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.b = rgbMax;
    if (hsv.b == 0)
    {
        hsv.r = 0;
        hsv.g = 0;
        return hsv;
    }

    hsv.g = 255 * long(rgbMax - rgbMin) / hsv.b;
    if (hsv.g == 0)
    {
        hsv.r = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.r = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.r = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.r = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}

Color Color::White = Color(255, 255, 255);
Color Color::Black = Color(0, 0, 0);
Color Color::Red = Color(255, 0, 0);
Color Color::Green = Color(0, 255, 0);
Color Color::Blue = Color(0, 0, 255);

} /* hx3d */
