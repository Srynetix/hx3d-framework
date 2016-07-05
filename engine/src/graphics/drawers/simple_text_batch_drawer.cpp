/*
    Simple text batch drawer.
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

#include "hx3d/graphics/drawers/simple_text_batch_drawer.hpp"

#include "hx3d/graphics/batches/batch.hpp"
#include "hx3d/graphics/texture.hpp"

#include "hx3d/graphics/text.hpp"

namespace hx3d {
namespace graphics {

SimpleTextBatchDrawer::SimpleTextBatchDrawer(): BatchDrawer() {}

void SimpleTextBatchDrawer::drawWithBatch(Batch* batch, Mesh* mesh) {

  // Should be a text
  auto text = (Text*)mesh;

  Texture::use(text->getFont(), text->getCharacterSize());
  Pointer<Shader> currentShader = batch->getShader();
  Pointer<Shader> textShader = text->getFont()->getShader();

  batch->setShader(textShader);
  batch->begin();

  float oldX = text->transform.position.x;

  if (text->isCenterAligned()) {
    text->transform.position.x -= text->getLength() / 2;
  }

  auto model = text->transform.compute();
  text->transform.position.x = oldX;

  textShader->setUniformMatrix4f("u_model", model);
  text->draw(textShader);

  batch->setShader(currentShader);
  batch->begin();

  Texture::disable();
}

} /* graphics */
} /* hx3d */
