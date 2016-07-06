/*
    Attribute array buffer.
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

#include "hx3d/graphics/buffers/array_buffer.hpp"
#include "hx3d/graphics/buffers/attribute.hpp"

namespace hx3d {
namespace graphics {
namespace buffers {

/**
@brief Attribute specialized array buffer.
*/
class AttributeArrayBuffer: public ArrayBuffer<float> {

public:
  /**
  @brief Construct an empty attribute array buffer.

  See @link create @endlink to initialize it.
  */
  AttributeArrayBuffer();

  /**
  @brief Construct an empty but initialized attribute array buffer.

  @param attribute Attribute
  */
  AttributeArrayBuffer(const Attribute attribute);

  /**
  @brief Construct an initialized attribute array buffer with values.

  @param attribute      Attribute
  @param values         Values
  */
  AttributeArrayBuffer(const Attribute attribute, const std::vector<float> values);
  ~AttributeArrayBuffer();

  /**
  @brief Initialize the attribute array buffer.

  @param attribute      Attribute
  */
  void create(const Attribute attribute);

  /**
  @brief Get the attribute.

  @return Attribute
  */
  Attribute& getAttribute();

  virtual void upload() override;

  virtual void begin(const Pointer<Shader>& shader) override;
  virtual void end(const Pointer<Shader>& shader) override;

protected:
  /// @brief Attribute
  Attribute _attribute;
};

} /* buffers */
} /* graphics */
} /* hx3d */
