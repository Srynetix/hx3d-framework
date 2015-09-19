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

#ifndef HX3D_GRAPHICS_UTILS_ATTRIBUTEARRAYBUFFER
#define HX3D_GRAPHICS_UTILS_ATTRIBUTEARRAYBUFFER

#include "hx3d/graphics/utils/array_buffer.hpp"

#include "hx3d/graphics/utils/attribute.hpp"

namespace hx3d {

class AttributeArrayBuffer: public ArrayBuffer<float> {

public:
  /**
  Construct an empty attribute array buffer.

  See @link#create to initialize it.
  */
  AttributeArrayBuffer();
  ~AttributeArrayBuffer();

  /**
  Construct an empty but initialized attribute array buffer.

  @param attribute Attribute
  */
  AttributeArrayBuffer(Attribute attribute);

  /**
  Construct an initialized attribute array buffer with values.

  @param attribute      Attribute
  @param values         Values
  */
  AttributeArrayBuffer(Attribute attribute, std::vector<float> values);

  /**
  Initialize the attribute array buffer.

  @param attribute      Attribute
  */
  void create(Attribute attribute);

  /**
  Get the attribute.

  @return Attribute
  */
  Attribute& getAttribute();

  virtual void upload() override;

  virtual void begin(Ptr<Shader> shader) override;
  virtual void end(Ptr<Shader> shader) override;

protected:
  Attribute _attribute;
};

} /* hx3d */

#endif
