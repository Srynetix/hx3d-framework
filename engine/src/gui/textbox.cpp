/*
    GUI textbox.

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

#include "hx3d/gui/textbox.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/event_manager.hpp"

namespace hx3d {
namespace gui {

TextBox::TextBox(const Widget::Ptr& parent): Label(parent) {
  registerAction("validate");
  _text->setCenterAlignment(false);
}

void TextBox::onFocusEnter() {
  _shape->setTint(Color(127, 127, 0));

  Core::Events()->beginTextInput();
}

void TextBox::onFocusExit() {
  _shape->setTint(Color(127, 127, 127));

  Core::Events()->endTextInput();
}

void TextBox::update(float delta) {
  Widget::update(delta);

  _text->transform.position.x = _transform.position.x - _transform.size.x / 2;
  _text->transform.position.y = _transform.position.y;
}

void TextBox::setText(std::string text) {
  Label::setText(text);

  _content = text;
}

void TextBox::keyPressed(KeyEvent::Key key) {
  if (key == KeyEvent::Key::Return) {
    send("validate");
  }

  else if (key == KeyEvent::Key::Backspace) {
    if (_content.size() > 0) {
      _content.pop_back();
    }

    _updateText();
  }
}

void TextBox::textInput(std::string text) {
  _content += text;
  _updateText();
}

void TextBox::_updateText() {
  _text->setContent(_content);
}

} /* gui */
} /* hx3d */
