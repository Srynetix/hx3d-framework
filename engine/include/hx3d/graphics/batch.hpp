/*
    Batch.
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

#ifndef HX3D_GRAPHICS_BATCH
#define HX3D_GRAPHICS_BATCH

#include "hx3d/graphics/base_batch.hpp"

namespace hx3d {

namespace graphics {

class Shader;
class Camera;

/**
@brief Simple base batch implementation. Draw at each draw call.
*/
class Batch: public BaseBatch {
  HX3D_PTR(Batch)

public:
  Batch();

  virtual void begin() override;
  virtual void end() override;
  virtual void draw(const Pointer<Mesh>& mesh) override;
  virtual void draw(const Pointer<gui::Text>& text) override;
  virtual void draw(const Pointer<gui::Text>& text, math::Function function) override;
};

} /* graphics */
} /* hx3d */

#endif
