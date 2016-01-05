/*
    GUI button.
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

#ifndef HX3D_GUI_BUTTON
#define HX3D_GUI_BUTTON

#include "hx3d/gui/widget.hpp"
#include "hx3d/gui/text.hpp"

namespace hx3d {
namespace gui {

/**
@brief GUI text button
*/
class Button: public Text {
public:
  /**
  @brief Create a text button.

  @param parent Parent widget
  @param font   Font
  */
  Button(Ptr<Widget> parent, Ptr<Font> font);

  virtual void draw(Ptr<Shader> shader) override;

  void functionDraw(Ptr<Shader> shader, math::Function function) = delete;
};

} /* gui */
} /* hx3d */

#endif
