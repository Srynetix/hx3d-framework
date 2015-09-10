/*
    Base VBO.
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

#ifndef HX3D_GRAPHICS_UTILS_VBO
#define HX3D_GRAPHICS_UTILS_VBO

#include "hx3d/graphics/utils/index_array_buffer.hpp"
#include "hx3d/graphics/utils/attribute_array_buffer.hpp"

#include <map>

namespace hx3d {

class VBO {

public:
  VBO();
  virtual ~VBO();

  /**
  Upload all the buffers.
  */
  void uploadAll();

  /**
  Upload the index buffer.
  */
  void uploadIndices();

  /**
  Upload the wanted attribute buffer.

  @param name Attribute name
  */
  void uploadAttribute(std::string name);

  /**
  Draw the VBO.

  @param shader Shader (Ptr)
  */
  void draw(Ptr<Shader> shader);

  /**
  Add an empty initialized attribute array buffer.

  @param name Attribute name
  @param type Attribute type
  @param size Attribute size
  */
  void addAttribute(std::string name, std::string shaderName, GLenum type, GLuint size);

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

protected:
  std::map<std::string, AttributeArrayBuffer> attributes;
  IndexArrayBuffer indices;
};

} /* hx3d */

#endif
