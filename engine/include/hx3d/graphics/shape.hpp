/*
    Shape.
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

#include "hx3d/graphics/mesh.hpp"

namespace hx3d {
namespace graphics {

/**
@brief 2D shape manipulation.
*/
class Shape: public Mesh {
  HX3D_PTR_REF(Shape)

public:

  /**
  @brief Create a shape.
  */
  Shape();

  void setBorderWidth(float width);
  float getBorderWidth() const;
  void setBorderColor(Color color);
  Color& getBorderColor();

  virtual void draw(const Pointer<Shader>& shader) override;

private:
  /// @brief Border width
  float _borderWidth;
  /// @brief Border color
  Color _borderColor;
};

} /* graphics */
} /* hx3d */
