/*
    Multi array buffer.
    One buffer for multiple attributes.

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


    TODO
    > Finish the class.
*/

#ifndef HX3D_GRAPHICS_BUFFERS_MULTIARRAYBUFFER
#define HX3D_GRAPHICS_BUFFERS_MULTIARRAYBUFFER

#include "hx3d/graphics/buffers/attribute_array_buffer.hpp"

#include <map>

namespace hx3d {
namespace graphics {
namespace buffers {

/**
@brief Multi-component array buffer for optimization purpose
*/
class MultiArrayBuffer: public ArrayBuffer<float> {

public:
  MultiArrayBuffer();
  ~MultiArrayBuffer();

  /**
  @brief Add an empty initialized attribute array buffer.

  @param name      Name
  @param attribute Attribute
  */
  void addAttribute(const std::string name, const Attribute attribute);

  /**
  @brief Set the wanted attribute array buffer content.

  @param name Attribute name
  @param data Values
  */
  void setAttribute(const std::string name, const std::vector<float> data);

  /**
  @brief Get the wanted attribute array buffer.

  @param name Attribute name
  @return Attribute array buffer
  */
  AttributeArrayBuffer& getAttribute(const std::string name);

  /**
  @brief Generate the vector using the attributes.
  */
  void generate();

  virtual void upload() override;

  virtual void begin(const Pointer<Shader>& shader) override;
  virtual void end(const Pointer<Shader>& shader) override;

private:
  /// @brief Attributes map
  std::map<std::string, AttributeArrayBuffer> _attributes;

  /**
  @brief Get an attribute.

  @param i Attribute

  @return AttributeArrayBuffer
  */
  AttributeArrayBuffer& getMapAttribute(const unsigned int i);

  /**
  @brief Get the total number of attributes

  @return Number of attributes
  */
  unsigned int attributeTotalSize();
};

} /* buffers */
} /* graphics */
} /* hx3d */

#endif
