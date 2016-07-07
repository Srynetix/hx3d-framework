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

#pragma once

#include "hx3d/gui/label.hpp"
#include "hx3d/utils/timer.hpp"

namespace hx3d {
namespace gui {

class TextBox: public Label {
  HX3D_PTR_REF(TextBox)

public:
  TextBox(const Widget::Ptr& parent = nullptr);

  virtual void onFocusEnter() override;
  virtual void onFocusExit() override;

  const std::string& getText();
  void setText(const std::string& text);

  virtual void update(float delta) override;

  virtual void keyPressed(window::KeyEvent::Key key) override;
  virtual void textInput(std::string text) override;

private:
  void _updateText();

  std::string _content;
  bool _shownCursor;

  Timer _timer;
};

} /* gui */
} /* hx3d */
