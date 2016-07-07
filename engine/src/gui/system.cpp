/*
    GUI system.
    Manage a GUI instance.

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

#include "hx3d/gui/system.hpp"
#include "hx3d/core/core.hpp"

#include "hx3d/window/event_manager.hpp"
#include "hx3d/graphics/batches/batch.hpp"
#include "hx3d/gui/widget.hpp"

namespace hx3d {
namespace gui {

System::System(const Pointer<Widget>& content) {
  setContent(content);
}

System::~System() {
  unregisterHandler();
}

void System::setContent(const Pointer<Widget>& content) {
  if (_content) unregisterHandler();
  _content = content;

  if (_content->_visible) {
    _content->_hasFocus = true;
    _content->onShow();
    _content->onFocusEnter();
  }

  registerHandler();
}

const Pointer<Widget>& System::getContent() {
  return _content;
}

void System::registerHandler() {
  if (_content)
    Core::Events()->registerHandler(_content.get());
}

void System::unregisterHandler() {
  if (_content) {
    _content->_hasFocus = false;
    Core::Events()->unregisterHandler(_content.get());
  }
}

void System::update(float delta) {
  if (_content)
    _content->update(delta);
}

void System::draw(const Pointer<graphics::Batch>& batch) {
  if (_content) {
    _content->draw(batch);
  }
}

} /* gui */
} /* hx3d */
