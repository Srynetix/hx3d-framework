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

#ifndef HX3D_GRAPHICS_ORDEREDBATCH
#define HX3D_GRAPHICS_ORDEREDBATCH

#include "hx3d/graphics/base_batch.hpp"

namespace hx3d {

namespace graphics {

class Shader;
class Camera;

/**
@brief Draw ordered meshes and texts on screen.
*/
class OrderedBatch: public BaseBatch {

public:
  OrderedBatch();

  virtual void begin() override;
  virtual void end() override;
  virtual void draw(const Ptr<Mesh>& mesh) override;
  virtual void draw(const Ptr<gui::Text>& text) override;
  virtual void draw(const Ptr<gui::Text>& text, math::Function function) override;

private:
  /// @brief Sorted mesh
  std::vector<std::pair<glm::mat4, Ptr<Mesh>>> _meshes;
  /// @brief Texts
  std::vector<Ptr<gui::Text>> _texts;
  /// @brief Function texts
  std::vector<std::pair<Ptr<gui::Text>, math::Function>> _funcTexts;
};

} /* graphics */
} /* hx3d */

#endif
