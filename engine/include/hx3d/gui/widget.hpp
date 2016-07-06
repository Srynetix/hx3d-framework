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

#pragma once

#include "hx3d/window/input_handler.hpp"

#include "hx3d/graphics/shape.hpp"

#include <map>

namespace hx3d {

namespace graphics {
  class Batch;
}

/**
@brief 2D/3D GUI components
*/
namespace gui {

class Widget: public std::enable_shared_from_this<Widget>, public window::InputHandler {
  HX3D_PTR_REF(Widget)

public:
  Widget(Pointer<Widget> parent = nullptr);
  virtual ~Widget();

  virtual void update(float delta);
  virtual void draw(const Pointer<graphics::Batch>& batch);

  void on(std::string action, std::function<void()> func);
  bool isVisible() const;

  friend class System;
  friend class Container;
  friend class Placement;

protected:
  virtual void onFocusEnter();
  virtual void onFocusExit();
  virtual void onShow();
  virtual void onHide();

  void registerAction(std::string action);
  void send(std::string action);

  graphics::Transform _transform;
  Pointer<graphics::Shape> _shape;
  Pointer<Widget> _parent;
  bool _visible;
  std::map<std::string, std::function<void()>> _actions;

  bool checkBounds(glm::vec2 position);

  ///////////////////
  // Input handler

  virtual void onMouseClicked(window::MouseButtonEvent::Button button, glm::vec2 mousePosition) override;
  virtual void onKeyPressed(window::KeyEvent::Key key) override;
  virtual void onTextInput(std::string text) override;

  /////////////////////
  // Widget handlers

  virtual void mouseClicked(window::MouseButtonEvent::Button button, glm::vec2 mousePosition);
  virtual void keyPressed(window::KeyEvent::Key key);
  virtual void textInput(std::string text);
};

} /* gui */
} /* hx3d */
