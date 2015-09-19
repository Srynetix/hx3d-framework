/*
    Multi VBO.
    Contains one index array buffer and multiple attributes array buffers.

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

#ifndef HX3D_GRAPHICS_UTILS_MULTIVBO
#define HX3D_GRAPHICS_UTILS_MULTIVBO

#include "hx3d/graphics/utils/index_array_buffer.hpp"
#include "hx3d/graphics/utils/multi_array_buffer.hpp"

#include <map>

namespace hx3d {

class MultiVBO {

public:
  MultiVBO();
  virtual ~MultiVBO();

  /**
  Upload all the buffers.
  */
  void uploadAll();

  /**
  Upload the index buffer.
  */
  void uploadIndices();

  /**
  Draw the VBO.

  @param shader Shader (Ptr)
  */
  void draw(Ptr<Shader> shader);

  /**
  Add an empty initialized attribute array buffer.

  @param name      Name
  @param attribute Attribute
  */
  void addAttribute(std::string name, Attribute attribute);

  /**
  Set the wanted attribute array buffer content.

  @param name Attribute name
  @param data Values
  */
  void setAttribute(std::string name, std::vector<float> data);

  /**
  Get the wanted attribute array buffer.

  @param name Attribute name
  @return Attribute array buffer
  */
  AttributeArrayBuffer& getAttribute(std::string name);

  /**
  Set the index buffer values.

  @param data Values
  */
  void setIndices(std::vector<GLushort> data);

  /**
  Get the index buffer.

  @return Index buffer.
  */
  IndexArrayBuffer& getIndices();

  /**
  Get the multi buffer.

  @¶eturn Multi buffer.
  */
  MultiArrayBuffer& getMultiBuffer();

protected:
  MultiArrayBuffer multiBuffer;
  IndexArrayBuffer indices;
};

} /* hx3d */

#endif
