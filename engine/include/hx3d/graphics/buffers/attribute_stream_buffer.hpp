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

#ifndef HX3D_GRAPHICS_BUFFERS_ATTRIBUTESTREAMBUFFER
#define HX3D_GRAPHICS_BUFFERS_ATTRIBUTESTREAMBUFFER

#include "hx3d/graphics/buffers/array_buffer.hpp"
#include "hx3d/graphics/buffers/attribute.hpp"

namespace hx3d {

class AttributeStreamBuffer: public ArrayBuffer<float> {

public:
  /**
  Construct an empty attribute array buffer.

  See @link#create to initialize it.
  */
  AttributeStreamBuffer();
  ~AttributeStreamBuffer();

  /**
  Construct an empty but initialized attribute array buffer.

  @param attribute Attribute
  */
  AttributeStreamBuffer(const Attribute attribute, const unsigned int stream_size);

  /**
  Initialize the attribute array buffer.

  @param attribute      Attribute
  */
  void create(const Attribute attribute, const unsigned int stream_size);

  /**
  Get the attribute.

  @return Attribute
  */
  Attribute& getAttribute();

  virtual void upload() override;

  virtual void begin(const Ptr<Shader>& shader) override;
  virtual void end(const Ptr<Shader>& shader) override;

protected:
  Attribute _attribute;
  unsigned int _stream_size;
};

} /* hx3d */

#endif
