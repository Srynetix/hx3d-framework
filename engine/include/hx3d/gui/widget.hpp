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

#ifndef HX3D_GUI_WIDGET
#define HX3D_GUI_WIDGET

#include "hx3d/graphics/mesh.hpp"
#include "hx3d/window/event_manager.hpp"

namespace hx3d {

/**
@brief 2D/3D GUI components
*/
namespace gui {

using namespace ::hx3d::graphics;

/**
@brief Base GUI element
*/
class Widget: public graphics::Mesh {
public:
  /**
  @brief Construct a widget from a parent widget.

  @param parent Widget (Ptr)
  */
  Widget(Widget* parent);

  /**
  @brief Add a widget to the list.

  @param widget Widget (Ptr)
  */
  void add(Ptr<Widget> widget);

  virtual void draw(Ptr<Shader> shader) override;

private:
  /// @brief Parent widget
  Widget* _parent;
  /// @brief Children widgets
  std::vector<Ptr<Widget>> _children;
};

} /* gui */
} /* hx3d */

#endif
