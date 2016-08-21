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

#pragma once

#include <glm/vec4.hpp>

namespace hx3d {
namespace graphics {

/**
@brief Four [0..255] components defined color
*/
class Color {

public:
  /**
  @brief Create a white color.
  */
  Color();

  /**
  @brief Create a color with an alpha of 255.

  @param r Red
  @param g Green
  @param b Blue
  */
  Color(unsigned char r, unsigned char g, unsigned char b);

  /**
  @brief Create a color with a custom alpha.

  @param r Red
  @param g Green
  @param b Blue
  @param a Alpha
  */
  Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

  /**
  @brief Affect a color into another.

  @param color Anothe color

  @return Color
  */
  Color& operator=(const Color& color);

  /**
  @brief Convert the color to a float format (between 0 and 1).

  @return Color (vec4)
  */
  glm::vec4 toFloat();

  bool operator==(const Color& color);
  bool operator!=(const Color& color);

  /////////////////

  /**
  @brief Convert HSV color to RGB format.

  @param hsv HSV color

  @return RGB color
  */
  static Color hsvToRgb(Color hsv);

  /**
  @brief Convert RGB color to HSV format.

  @param rgb RGB color

  @return HSV color
  */
  static Color rgbToHsv(Color rgb);

  /// @brief Red component
  unsigned char r;
  /// @brief Green component
  unsigned char g;
  /// @brief Blue component
  unsigned char b;
  /// @brief Alpha component
  unsigned char a;

  //////////////////

  /// @brief White color
  static Color White;
  /// @brief Black color
  static Color Black;
  /// @brief Red color
  static Color Red;
  /// @brief Green color
  static Color Green;
  /// @brief Blue color
  static Color Blue;
};

} /* graphics */
} /* hx3d */
