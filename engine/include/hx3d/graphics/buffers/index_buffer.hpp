#pragma once

#include "hx3d/graphics/buffers/buffer.hpp"

namespace hx3d {
namespace graphics {
namespace buffers {

template<class T>
class IndexBuffer : public Buffer<T> {

public:
  IndexBuffer() :
    Buffer<T>() {}

  IndexBuffer(std::vector<T> &values) :
    Buffer<T>() {
    this->set(values);
  }

  virtual ~IndexBuffer() {}

  virtual void upload(GLenum bufferType = GL_STATIC_DRAW) {
    if (this->_vector.size() > 0) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_buf);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_vector.size() * sizeof(T), this->_vector.data(), bufferType);
    }
  }

  virtual void bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_buf);
  }

  virtual void draw(GLenum drawPrimitive = GL_TRIANGLES);
};

template<>
inline void IndexBuffer<unsigned short>::draw(GLenum drawPrimitive) {
  if (this->_vector.size() > 0) {
    glDrawElements(drawPrimitive, (GLsizei) this->_vector.size(), GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
  }
}

} /* buffers */
} /* graphics */
} /* hx3d */
