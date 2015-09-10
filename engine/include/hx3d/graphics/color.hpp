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

#ifndef HX3D_GRAPHICS_COLOR
#define HX3D_GRAPHICS_COLOR

#include <glm/vec4.hpp>

namespace hx3d {

class Color {

public:
  /**
  Create a white color.
  */
  Color();

  /**
  Create a color with an alpha of 255.

  @param r Red
  @param g Green
  @param b Blue
  */
  Color(unsigned char r, unsigned char g, unsigned char b);

  /**
  Create a color with a custom alpha.

  @param r Red
  @param g Green
  @param b Blue
  @param a Alpha
  */
  Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

  /**
  Affect a color into another.
  @param color Anothe color
  @return Color
  */
  Color& operator=(const Color& color);

  /**
  Convert the color to a float format (between 0 and 1).

  @return Color (vec4)
  */
  glm::vec4 toFloat();

  /////////////////

  static Color interp(Color a, Color b, float t)
  {
    // 0.0 <= t <= 1.0
    Color ca = Color::rgbToHsv(a);
    Color cb = Color::rgbToHsv(b);
    Color final;

    final.r = Color::linear(ca.r, cb.r, t);
    final.g = Color::linear(ca.g, cb.g, t);
    final.b = Color::linear(ca.b, cb.b, t);

    return Color::hsvToRgb(final);
  }

  static int linear(int a, int b, float t)
  {
      return a * (1 - t) + b * t;
  }


  /**
  Convert HSV color to RGB format.

  @param hsv HSV color
  @return RGB color
  */
  static Color hsvToRgb(Color hsv);

  /**
  Convert RGB color to HSV format.

  @param rgb RGB color
  @return HSV color
  */
  static Color rgbToHsv(Color rgb);

  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;

  //////////////////

  static Color White;
  static Color Black;

  static Color Red;
  static Color Green;
  static Color Blue;
};

} /* hx3d */

#endif
