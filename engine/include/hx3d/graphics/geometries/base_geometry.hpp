/*
    Base geometry.
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

#ifndef HX3D_GRAPHICS_GEOMETRIES_BASEGEOMETRY
#define HX3D_GRAPHICS_GEOMETRIES_BASEGEOMETRY

#include "hx3d/graphics/buffers/attribute_array_buffer.hpp"
#include "hx3d/graphics/buffers/index_array_buffer.hpp"
#include "hx3d/graphics/shader.hpp"

using namespace hx3d::graphics::buffers;

namespace hx3d {
namespace graphics {

/**
@brief Mesh geometry types
*/
namespace geom {

/**
@brief Base geometry.
Must be inherited.
*/
class BaseGeometry {
public:
  BaseGeometry();

  /**
  @brief Add an attribute

  @param name Name
  @param attribute Attribute definition
  */
  void addAttribute(std::string name, Attribute attribute);

  /**
  @brief Set an attribute with values

  @param name Name
  @param values Values
  */
  void setAttribute(std::string name, std::vector<float> values);

  /**
  @brief Get an attribute array buffer

  @param name Name

  @return Attribute array buffer
  */
  AttributeArrayBuffer& getAttribute(std::string name);

  /**
  @brief Set the indices

  @param values Values
  */
  void setIndices(std::vector<GLushort> values);

  /**
  @brief Get the index array buffer

  @return Index array buffer
  */
  IndexArrayBuffer& getIndices();

  /**
  @brief Upload all the buffers to the GPU
  */
  void uploadAll();

  /**
  @brief Draw the geometry

  @param shader Shader
  */
  virtual void draw(Ptr<Shader> shader) = 0;

protected:
  /// @brief Attributes map
  std::map<std::string, AttributeArrayBuffer> _attributes;
  /// @brief Index array buffer
  IndexArrayBuffer _indices;
};

} /* geom */
} /* graphics */
} /* hx3d */

#endif
