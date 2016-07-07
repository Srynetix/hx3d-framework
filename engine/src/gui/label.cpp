/*
    GUI label.

    Copyright (C) 2016 Denis BOURGE

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

#include "hx3d/gui/label.hpp"

#include "hx3d/graphics/text.hpp"
#include "hx3d/graphics/batches/batch.hpp"

namespace hx3d {
namespace gui {

Label::Label(const Widget::Ptr& parent): Widget(parent) {
  _text = Make<graphics::Text>();
  _offset = {5.f, 0};
}

void Label::update(float delta) {
  Widget::update(delta);

  glm::vec2 new_pos = {_transform.position.x, _transform.position.y};
  if (!_text->isCenterAligned()) {
    new_pos += _offset;
  }

  _text->transform.position.x = new_pos.x;
  _text->transform.position.y = new_pos.y;
}

void Label::draw(const Pointer<graphics::Batch>& batch) {
  Widget::draw(batch);

  batch->draw(_text);
}

void Label::setText(const std::string& text) {
  _text->setContent(text);
}

const std::string& Label::getText() {
  return _text->getContent();
}

} /* gui */
} /* hx3d */
