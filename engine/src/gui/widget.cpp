/*
    Base widget.
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

#include "hx3d/gui/widget.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/graphics/shape.hpp"
#include "hx3d/graphics/batches/batch.hpp"
#include "hx3d/window/application.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace gui {

Widget::Widget(Pointer<Widget> parent) {
  _parent = parent;
  _visible = true;
  _hasFocus = false;
  _shape = Make<graphics::Shape>();
  _shape->setTint(graphics::Color(127, 127, 127));
}

Widget::~Widget() {
  onFocusExit();
  onHide();
}

void Widget::update(float delta) {
  _shape->transform.position.x = _transform.position.x;
  _shape->transform.position.y = _transform.position.y;
  _shape->transform.size.x = _transform.size.x;
  _shape->transform.size.y = _transform.size.y;
}

void Widget::draw(const Pointer<graphics::Batch>& batch) {
  batch->draw(_shape);
}

void Widget::onFocusEnter() {
}

void Widget::onFocusExit() {
}

void Widget::onShow() {
}

void Widget::onHide() {
}

bool Widget::isVisible() const {
  return _visible;
}

void Widget::registerAction(std::string action) {
  if (_actions.find(action) != _actions.end()) {
    Log.Error("action %s already registered", action.c_str());
  } else {
    _actions[action] = nullptr;
  }
}

void Widget::send(std::string action) {
  if (_actions.find(action) == _actions.end()) {
    Log.Error("action %s do not exist", action.c_str());
  } else {
    auto act = _actions[action];
    if (act != nullptr) {
      act();
    }
  }
}

void Widget::on(std::string action, std::function<void()> func) {
  if (_actions.find(action) == _actions.end()) {
    Log.Error("action %s do not exist", action.c_str());
  } else {
    _actions[action] = func;
  }
}

bool Widget::checkBounds(glm::vec2 position) {
  float lx = _transform.position.x - ((_transform.size.x / 2) * _transform.scale.x);
  float hx = _transform.position.x + ((_transform.size.x / 2) * _transform.scale.x);
  float ly = _transform.position.y - ((_transform.size.y / 2) * _transform.scale.y);
  float hy = _transform.position.y + ((_transform.size.y / 2) * _transform.scale.y);

  auto x_pos = position.x;
  auto y_pos = Core::App()->getHeight() - position.y;

  if (x_pos >= lx && x_pos <= hx && y_pos >= ly && y_pos <= hy) {
    return true;
  } else {
    return false;
  }
}

///////////////////
// Input handler

void Widget::onMouseClicked(window::MouseButtonEvent::Button button, glm::vec2 mousePosition) {
  mouseClicked(button, mousePosition);
}

void Widget::onKeyPressed(window::KeyEvent::Key key) {
  keyPressed(key);
}

void Widget::onTextInput(std::string text) {
  textInput(text);
}

/////////////////////
// Widget handlers

void Widget::mouseClicked(window::MouseButtonEvent::Button button, glm::vec2 mousePosition) {

}

void Widget::keyPressed(window::KeyEvent::Key key) {

}

void Widget::textInput(std::string text) {

}

} /* gui */
} /* hx3d */
