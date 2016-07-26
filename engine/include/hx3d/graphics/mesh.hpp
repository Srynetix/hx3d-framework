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

#pragma once

#include "hx3d/graphics/color.hpp"
#include "hx3d/graphics/transform.hpp"

#include "hx3d/utils/reference.hpp"

namespace hx3d {
namespace graphics {

class Shader;
class Batch;
class Geometry;
class BatchDrawer;
class GeometryDrawer;
class Color;

/**
@brief Displayable 2D/3D element.
*/
class Mesh {
  HX3D_PTR_REF(Mesh)

public:
  Mesh();
  Mesh(const Pointer<GeometryDrawer>& geoDrawer, const Pointer<BatchDrawer>& batchDrawer);
  virtual ~Mesh();

  /**
  @brief Draw the mesh using a shader.

  @param shader Shader (Ptr)
  */
  virtual void draw(const Pointer<Shader>& shader);

  /**
  @brief Draw the mesh using a batch.

  @param batch Batch (Ptr)
  */
  virtual void drawWithBatch(Batch* batch);

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

  @param geometry Geometry (Ptr)
  */
  void setGeometry(const Pointer<Geometry>& geometry);

  /**
  @brief Set the geometry drawer.

  @param drawer GeometryDrawer (Ptr)
  */
  void setGeometryDrawer(const Pointer<GeometryDrawer>& geoDrawer);

  /**
  @brief Set the batch drawer.

  @param drawer BatchDrawer (Ptr)
  */
  void setBatchDrawer(const Pointer<BatchDrawer>& batchDrawer);

  /**
  @brief Get the mesh geometry

  @return Geometry (Ptr)
  */
  Pointer<Geometry>& getGeometry();

  /**
  @brief Get the mesh geometry drawer

  @return GeometryDrawer (Ptr)
  */
  Pointer<GeometryDrawer>& getGeometryDrawer();

  /**
  @brief Get the batch drawer

  @return BatchDrawer (Ptr)
  */
  Pointer<BatchDrawer>& getBatchDrawer();

  /// @brief Mesh transformation
  Transform transform;

protected:
  /// @brief Tint color
  Color _tint;
  /// @brief Current geometry
  Pointer<Geometry> _geometry;
  /// @brief Current geometry drawer
  Pointer<GeometryDrawer> _geoDrawer;
  /// @brief Current batch drawer
  Pointer<BatchDrawer> _batchDrawer;
};

} /* graphics */
} /* hx3d */
