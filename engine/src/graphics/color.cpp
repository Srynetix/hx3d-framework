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

Color Color::White = Color(255, 255, 255);
Color Color::Black = Color(0, 0, 0);
Color Color::Red = Color(255, 0, 0);
Color Color::Green = Color(0, 255, 0);
Color Color::Blue = Color(0, 0, 255);

} /* hx3d */
