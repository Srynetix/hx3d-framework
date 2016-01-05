/*
    Stencil.
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

#include "hx3d/graphics/stencil.hpp"

namespace hx3d {
namespace graphics {

void Stencil::enable() {
  glEnable(GL_STENCIL_TEST);
}

void Stencil::disable() {
  glDisable(GL_STENCIL_TEST);
}

void Stencil::setFunction(Function func, int ref, int mask) {
  glStencilFunc(convertFunction(func), ref, mask);
}

void Stencil::setOperation(Operation sfail, Operation dpfail, Operation dppass) {
  glStencilOp(convertOperation(sfail), convertOperation(dpfail), convertOperation(dppass));
}

void Stencil::begin() {
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  glDepthMask(GL_FALSE);

  glStencilMask(0xFF);

  glClear(GL_STENCIL_BUFFER_BIT);
}

void Stencil::end() {
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  glDepthMask(GL_TRUE);

  glStencilMask(0x00);

  glStencilFunc(GL_EQUAL, 2, 0xFF);
}

GLenum Stencil::convertFunction(Function func) {
  return
    func == Function::Never ? GL_NEVER :
    func == Function::Always ? GL_ALWAYS :
    func == Function::Equal ? GL_EQUAL :
    func == Function::NotEqual ? GL_NOTEQUAL :
    func == Function::Less ? GL_LESS :
    func == Function::Greater ? GL_GREATER :
    func == Function::LessOrEqual ? GL_LEQUAL :
    GL_GEQUAL;
}

GLenum Stencil::convertOperation(Operation op) {
  return
    op == Operation::Keep ? GL_KEEP :
    op == Operation::Zero ? GL_ZERO :
    op == Operation::Replace ? GL_REPLACE :
    op == Operation::Increment ? GL_INCR :
    op == Operation::IncrementWrap ? GL_INCR_WRAP :
    op == Operation::Decrement ? GL_DECR :
    op == Operation::DecrementWrap ? GL_DECR_WRAP :
    GL_INVERT;
}

} /* graphics */
} /* hx3d */
