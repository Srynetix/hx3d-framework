/*
    Simple Batch 2D.
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

#include "hx3d/graphics/batches/batch.hpp"
#include "hx3d/utils/reference.hpp"

namespace hx3d {
namespace graphics {

class Shader;
class Camera;

/**
@brief Simple base batch implementation without Z. Draw at each draw call.
*/
class SimpleBatch2D: public Batch {
  HX3D_PTR_REF(SimpleBatch2D)

public:
  SimpleBatch2D();

  virtual void begin() override;
  virtual void end() override;
  virtual void draw(const Pointer<Mesh>& mesh) override;
};

} /* graphics */
} /* hx3d */