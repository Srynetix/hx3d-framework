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

#pragma once

#include "hx3d/utils/reference.hpp"

namespace hx3d {

namespace graphics {
  class Batch;
}

namespace gui {

class Widget;

class System {
  HX3D_PTR_REF(System)

public:
  System(const Pointer<Widget>& content = nullptr);
  ~System();

  void setContent(const Pointer<Widget>& content);
  const Pointer<Widget>& getContent();

  void enterFocus();
  void exitFocus();

  void registerHandler();
  void unregisterHandler();

  void update(float delta);
  void draw(const Pointer<graphics::Batch>& batch);

private:
  Pointer<Widget> _content;
};

} /* gui */
} /* hx3d */
