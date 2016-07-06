/*
    Simple shape batch drawer.
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

#include "hx3d/graphics/drawers/simple_shape_batch_drawer.hpp"

#include "hx3d/graphics/batches/batch.hpp"
#include "hx3d/graphics/mesh.hpp"
#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/shape.hpp"
#include "hx3d/utils/assets.hpp"

#include "hx3d/core/core.hpp"

namespace hx3d {
namespace graphics {

SimpleShapeBatchDrawer::SimpleShapeBatchDrawer(): BatchDrawer() {}

void SimpleShapeBatchDrawer::drawWithBatch(Batch* batch, Mesh* mesh) {

  // Should be shape
  Shape* shape = (Shape*)mesh;

  auto& prev_shader = batch->getShader();
  auto new_shader = Core::Assets()->get<Shader>("base_border");

  batch->end();
  batch->setShader(new_shader);
  batch->begin();

  auto model = mesh->transform.compute();
  new_shader->setUniformMatrix4f("u_model", model);
  new_shader->setUniform1f("u_borderWidth", shape->getBorderWidth());
  new_shader->setUniform2f("u_quadSize", {shape->transform.size.x, shape->transform.size.y});
  new_shader->setUniform4f("u_borderColor", shape->getBorderColor().toFloat());
  mesh->draw(new_shader);

  batch->end();
  batch->setShader(prev_shader);
}

} /* graphics */
} /* hx3d */
