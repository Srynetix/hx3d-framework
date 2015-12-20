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

#include "hx3d/graphics/geometry.hpp"

namespace hx3d {
namespace gui {

Widget::Widget(Ptr<Widget> parent): Mesh(),
  _parent(parent)
 {
  _geometry = Make<Geometry>();

  _geometry->setAttribute("Position", std::vector<float> {
    -0.5f, 0.5f, 0.f,
    0.5, 0.5f, 0.f,
    -0.5f, -0.5f, 0.f,
    0.5f, -0.5f, 0.f
  });

  _geometry->setIndices(std::vector<GLushort> {
    0, 1, 2,
    0, 2, 3
  });

  _geometry->setAttribute("Color", std::vector<float> {
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1
  });

  _geometry->setAttribute("Texture", std::vector<float> {
    0, 0,
    0, 1,
    1, 0,
    1, 1
  });

  _geometry->uploadAll();
}

void Widget::add(Ptr<Widget> widget) {
  widget->_parent.reset(this);
  _children.push_back(widget);
}

void Widget::draw(Ptr<Shader> shader) {
  Mesh::draw(shader);
}

} /* gui */
} /* hx3d */
