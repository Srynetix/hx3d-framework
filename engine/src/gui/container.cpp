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

#include "hx3d/gui/container.hpp"

namespace hx3d {
namespace gui {

Container::Container(const Pointer<Widget>& parent): Widget(parent) {
  _propagateEvent = true;
  _activeChild = nullptr;
}

void Container::addChild(const Widget::Ptr& widget) {
  widget->_parent = shared_from_this();
  _children.push_back(widget);
}

void Container::addChild(Placement placement) {
  auto widget = placement._widget;
  widget->_parent = shared_from_this();
  _children.push_back(placement.apply());
}

void Container::onMouseClicked(window::MouseButtonEvent::Button button, glm::vec2 mousePosition) {
  mouseClicked(button, mousePosition);

  if (_propagateEvent) {
    if (_activeChild && _activeChild->checkBounds(mousePosition)) {
      _activeChild->onMouseClicked(button, mousePosition);
    } else {
      // New active child
      for (auto& child: _children) {
        if (child != _activeChild && child->checkBounds(mousePosition)) {
          if (_activeChild) {
            _activeChild->onFocusExit();
            _activeChild->_hasFocus = false;
          }

          _activeChild = child;
          child->_hasFocus = true;
          child->onFocusEnter();
          child->onMouseClicked(button, mousePosition);
          return;
        }
      }

      // No active child
      if (_activeChild) {
        _activeChild->onFocusExit();
        _activeChild->_hasFocus = false;
        _activeChild = nullptr;
      }
    }
  }
}

void Container::onKeyPressed(window::KeyEvent::Key key) {
  keyPressed(key);

  if (_propagateEvent) {
    if (_activeChild) {
      _activeChild->onKeyPressed(key);
    }
  }
}

void Container::onTextInput(std::string text) {
  textInput(text);

  if (_propagateEvent) {
    if (_activeChild) {
      _activeChild->onTextInput(text);
    }
  }
}

void Container::update(float delta) {
  Widget::update(delta);
  for (auto& child: _children) {
    child->update(delta);
  }
}

void Container::draw(const Pointer<graphics::Batch>& batch) {
  Widget::draw(batch);

  if (_visible) {
    for (auto& child: _children) {
      child->draw(batch);
    }
  }
}

} /* gui */
} /* hx3d */
