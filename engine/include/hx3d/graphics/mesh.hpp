/*
    Mesh.
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

#ifndef HX3D_GRAPHICS_MESH
#define HX3D_GRAPHICS_MESH

#include "hx3d/graphics/color.hpp"

#include "hx3d/graphics/geometries/base_geometry.hpp"
#include "hx3d/graphics/transform.hpp"

#include "hx3d/utils/ptr.hpp"


namespace hx3d {
namespace graphics {

class Shader;
class Color;

/**
@brief Displayable 2D/3D element.
*/
class Mesh {

public:
  Mesh();

  /**
  @brief Draw the mesh using a shader.

  @param shader Shader (Ptr)
  */
  virtual void draw(Ptr<Shader> shader);

  /**
  @brief Set the mesh tint.

  Automatically update the color.
  See @link updateColor @endlink.

  @param tint Color
  */
  void setTint(Color tint);

  /**
  @brief Get the mesh tint.

  @return Tint
  */
  Color& getTint();

  /**
  @brief Update the mesh color from the tint.
  */
  void updateColor();

  /**
  @brief Set the mesh geometry.

  @param geometry BaseGeometry (Ptr)
  */
  void setGeometry(Ptr<geom::BaseGeometry> geometry);

  /**
  @brief Get the mesh geometry

  @return BaseGeometry (Ptr)
  */
  Ptr<geom::BaseGeometry>& getGeometry();

  /// @brief Mesh transformation
  Transform transform;

protected:
  /// @brief Tint color
  Color _tint;
  /// @brief Current geometry
  Ptr<geom::BaseGeometry> _geometry;
};

} /* graphics */
} /* hx3d */

#endif
