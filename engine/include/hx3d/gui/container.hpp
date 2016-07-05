/*
    GUI container.

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

#include "hx3d/gui/widget.hpp"

namespace hx3d {
namespace gui {

class Container: public Widget {
  HX3D_ONLY_PTR(Container)

public:
  Container(const Pointer<Widget>& parent = nullptr);

  void addChild(const Widget::Ptr& widget);

  virtual void onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) override;
  virtual void onKeyPressed(KeyEvent::Key key) override;
  virtual void onTextInput(std::string text) override;

  virtual void update(float delta) override;
  virtual void draw(const Pointer<Batch>& batch) override;

protected:
  bool _propagateEvent;
  Pointer<Widget> _activeChild;
  std::vector<Pointer<Widget>> _children;
};

} /* gui */
} /* hx3d */
