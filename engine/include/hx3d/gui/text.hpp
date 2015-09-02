/*
    GUI text.
    Render text.

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

#ifndef HX3D_GUI_TEXT
#define HX3D_GUI_TEXT

#include "hx3d/gui/widget.hpp"

#include "hx3d/math/function.hpp"

namespace hx3d {

class Font;

namespace gui {

class Text: public Widget {

public:
  /**
  Create a text from a font.
  @param font Font (Ptr)
  */
  Text(Ptr<Font> font);

  /**
  Create a text from a parent widget and a font.

  @param parent Widget (Ptr)
  @param Font   Font (Ptr)
  */
  Text(Ptr<Widget> parent, Ptr<Font> font);

  /**
  Set the text content.
  @param content Content
  */
  void setContent(std::string content);

  /**
  Draw the text following a function.

  @param shader Shader (Ptr)
  @param function  Function
  */
  void functionDraw(Ptr<Shader> shader, math::Function function);

  /**
  Get the text font.
  @return Font (Ptr)
  */
  Ptr<Font> getFont();

  virtual void draw(Ptr<Shader> shader) override;

protected:

  /**
  Initialize the text.
  */
  void init();

  Ptr<Font> _font;
  std::string _content;
};

} /* gui */
} /* hx3d */

#endif
