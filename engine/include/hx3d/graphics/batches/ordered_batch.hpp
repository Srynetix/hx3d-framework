/*
    Ordered Batch.
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

namespace hx3d {
namespace graphics {

class Shader;
class Mesh;
class Camera;

/**
@brief Draw ordered meshes and texts on screen.
*/
class OrderedBatch: public Batch {

public:
  OrderedBatch();

  virtual void begin() override;
  virtual void end() override;
  virtual void draw(const Pointer<Mesh>& mesh) override;

private:
  /// @brief Sorted meshes
  std::vector<std::pair<glm::mat4, Pointer<Mesh>>> _meshes;
};

} /* graphics */
} /* hx3d */
