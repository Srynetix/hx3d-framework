/*
    Framebuffer.
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

#include "hx3d/graphics/frame_buffer.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/core/application.hpp"

#include "hx3d/graphics/texture.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {

GLint FrameBuffer::_defaultID = 0;

FrameBuffer::FrameBuffer():
  FrameBuffer(Core::App()->getWidth(), Core::App()->getHeight())
{}

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height):
  _width(width),
  _height(height)
{
  create();
}

void FrameBuffer::fetchDefaultFrameBuffer() {
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultID);
}

void FrameBuffer::create() {
  if (glIsFramebuffer(_id) == GL_TRUE)
      glDeleteFramebuffers(1, &_id);

    // Génération d'un id
    glGenFramebuffers(1, &_id);

    glBindFramebuffer(GL_FRAMEBUFFER, _id);

    _colorBuffer = Texture::createColorBuffer(_width, _height);
    createRenderBuffer(_depthBuffer, GL_DEPTH_COMPONENT16);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorBuffer->getID(), 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
      glDeleteFramebuffers(1, &_id);
      glDeleteRenderbuffers(1, &_depthBuffer);

      Log.Error("FBO Error.");
    }
    else {
      Log.Info(format("FBO created (size: %dx%d).", _width, _height));
    }

    glBindFramebuffer(GL_FRAMEBUFFER, _defaultID);
}

void FrameBuffer::use(Ptr<FrameBuffer> buffer) {
  glBindFramebuffer(GL_FRAMEBUFFER, buffer->_id);
  glViewport(0, 0, buffer->_width, buffer->_height);
}

void FrameBuffer::useDefault() {
  glBindFramebuffer(GL_FRAMEBUFFER, _defaultID);
  glViewport(0, 0, Core::App()->getWidth(), Core::App()->getHeight());
}

Ptr<Texture> FrameBuffer::getColorBuffer() {
  return _colorBuffer;
}

void FrameBuffer::createRenderBuffer(GLuint& id, GLenum format) {

  if(glIsRenderbuffer(id) == GL_TRUE)
        glDeleteRenderbuffers(1, &id);

  glGenRenderbuffers(1, &id);

  glBindRenderbuffer(GL_RENDERBUFFER, id);

  glRenderbufferStorage(GL_RENDERBUFFER, format, _width, _height);

  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

} /* hx3d */
