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

#include "hx3d/graphics/font.hpp"
#include "hx3d/math/function.hpp"

namespace hx3d {
namespace gui {

/**
@brief Text GUI element
*/
class Text: public Widget {

public:

  /**
  @brief Create a text without font.
  See @link setFont @endlink.
  */
  Text();

  /**
  @brief Create a text from a font.

  @param font Font (Ptr)
  */
  Text(Ptr<Font> font);

  /**
  @brief Create a text from a parent widget and a font.

  @param parent Widget (Ptr)
  @param font   Font (Ptr)
  */
  Text(Widget* parent, Ptr<Font> font);

  /**
  @brief Set the font.

  @param font Font (Ptr)
  */
  void setFont(Ptr<Font> font);

  /**
  @brief Set the character size

  @param size Size
  */
  void setCharacterSize(int size);

  /**
  @brief Set the center alignment

  @param value True/False
  */
  void setCenterAlignment(bool value);

  /**
  @brief Set the text content.

  @param content Content
  */
  void setContent(std::string content);

  /**
  @brief Draw the text following a function.

  @param shader Shader (Ptr)
  @param function  Function
  */
  void functionDraw(const Ptr<Shader>& shader, math::Function function);

  /**
  @brief Get the text font.

  @return Font (Ptr)
  */
  Ptr<Font> getFont();

  /**
  @brief Get the character size

  @return Character size
  */
  int getCharacterSize();

  /**
  @brief Get the text length

  @return Text length
  */
  float getLength();

  /**
  @brief Is the text center aligned ?

  @return True/False
  */
  bool isCenterAligned();

  virtual void draw(const Ptr<Shader>& shader) override;

protected:

  /**
  @brief Initialize the text.
  */
  void init();

  /**
  @brief Calculate the text length
  */
  float calculateLength();

  /// @brief Text font
  Ptr<Font> _font;
  /// @brief Text content
  std::string _content;
  /// @brief Text length
  float _length;
  /// @brief Character size
  int _characterSize;
  /// @brief Is the text center aligned ?
  bool _centerAligned;
};

} /* gui */
} /* hx3d */

#endif
