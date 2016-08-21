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
#include "hx3d/graphics/text.hpp"

namespace hx3d {
namespace gui {

TextBox::TextBox(const Widget::Ptr& parent): Label(parent) {
  registerAction("validate");
  _text->setCenterAlignment(false);
  _timer.initialize(600);

  _shownCursor = false;
}

void TextBox::onFocusEnter() {
  _shape->setTint(graphics::Color(127, 64, 0));
  _text->setContent(_text->getContent() + "_");
  _shownCursor = true;

  Core::Events()->beginTextInput();
}

void TextBox::onFocusExit() {
  _shape->setTint(graphics::Color(127, 127, 127));
  _timer.reset();
  _shownCursor = false;
  _updateText();

  Core::Events()->endTextInput();
}

void TextBox::update(float delta) {
  Label::update(delta);

  if (_hasFocus) {
    _timer.update(delta);

    if (_shownCursor) {
      if (_timer.hasEnded()) {
        _updateText();
        _timer.reset();
        _shownCursor = false;
      }
    } else {
      if (_timer.hasEnded()) {
        _text->setContent(_text->getContent() + "_");
        _timer.reset();
        _shownCursor = true;
      }
    }
  }

  if (!_text->isCenterAligned())
    _text->move(-getSize().x / 2, 0);
}

void TextBox::setText(const std::string& text) {
  Label::setText(text);

  _content = text;
}

void TextBox::keyPressed(window::KeyEvent::Key key) {
  if (key == window::KeyEvent::Key::Return) {
    _shownCursor = false;
    _updateText();

    send("validate");
  }

  else if (key == window::KeyEvent::Key::Backspace) {
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
