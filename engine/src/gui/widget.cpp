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
#include "hx3d/graphics/geometries/geometry.hpp"
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
  _shape->getGeometry()->uploadAll();
}

Widget::~Widget() {
//  std::enable_shared_from_this<Widget>::~enable_shared_from_this();

  onFocusExit();
  onHide();
}

void Widget::update(float delta) {
  _shape->setPosition(this->get3DPosition());
  _shape->setSize(this->get3DSize());
  _shape->setScale(this->get3DScale());
  _shape->setRotation(this->get3DRotation());
}

void Widget::draw(const Pointer<graphics::Batch>& batch) {
  if (_visible) {
    batch->draw(_shape);
  }
}

void Widget::show() {
  _visible = true;
  onShow();
}

void Widget::hide() {
  _visible = false;
  onHide();
}

void Widget::enterFocus() {
  _hasFocus = true;
  onFocusEnter();
}

void Widget::exitFocus() {
  _hasFocus = false;
  onFocusExit();
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
  auto Log = Logger::getLogger("gui");

  if (_actions.find(action) != _actions.end()) {
    Log.Error("action %s already registered", action.c_str());
  } else {
    _actions[action] = nullptr;
  }
}

void Widget::send(std::string action) {
  auto Log = Logger::getLogger("gui");

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
  auto Log = Logger::getLogger("gui");

  if (_actions.find(action) == _actions.end()) {
    Log.Error("action %s do not exist", action.c_str());
  } else {
    _actions[action] = func;
  }
}

bool Widget::checkBounds(glm::vec2 position) {
  float lx = getPosition().x - ((getSize().x / 2) * getScale().x);
  float hx = getPosition().x + ((getSize().x / 2) * getScale().x);
  float ly = getPosition().y - ((getSize().y / 2) * getScale().y);
  float hy = getPosition().y + ((getSize().y / 2) * getScale().y);

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
