/*
    Image button.
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

#ifndef HX3D_GUI_IMAGE_BUTTON
#define HX3D_GUI_IMAGE_BUTTON

#include "hx3d/graphics/sprite.hpp"

namespace hx3d {
namespace gui {

class ImageButton: public Sprite {
  public:
    ImageButton() {}

    void setOnClickCallback(std::function<void()> func) {
      this->func = func;
    }

    void onClick(glm::vec2 position) {
      if (transform.contains(position)) {
        if (func) func();
      }
    }

  private:
    std::function<void()> func;
};

} /* gui */
} /* hx3d */

#endif /* HX3D_GUI_IMAGE_BUTTON */
