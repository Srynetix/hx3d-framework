#pragma once

#include "hx3d/graphics/buffers/buffer.hpp"
#include "hx3d/graphics/buffers/attribute.hpp"
#include "hx3d/graphics/shader.hpp"

#include "hx3d/utils/log.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

namespace hx3d {
namespace graphics {
namespace buffers {

template<class T>
class AttributeBuffer : public Buffer<T> {

public:
  AttributeBuffer():
    Buffer<T>(), _uploaded(false) {}

  AttributeBuffer(const Attribute attribute) :
    Buffer<T>(), _uploaded(false), _attribute(attribute) {}

  AttributeBuffer(const Attribute attribute, const std::vector<T> values) :
    AttributeBuffer(attribute) {
    this->set(values);
  }

  virtual ~AttributeBuffer() {}

  Attribute &getAttributeDefinition() {
    return _attribute;
  }

  virtual void create(const Attribute attribute) {
    _attribute = attribute;
  }

  virtual void upload(GLenum drawMode = GL_STATIC_DRAW) {
    if (this->_vector.size() > 0) {
      glBindBuffer(GL_ARRAY_BUFFER, this->_buf);
      glBufferData(GL_ARRAY_BUFFER, this->_vector.size() * sizeof(T), this->_vector.data(), drawMode);

      _uploaded = true;
    }
  }

  virtual void bind(const Pointer<Shader> &shader) {
    if (this->_vector.size() > 0) {
      const GLuint loc = shader->getAttribute(this->_attribute.getName());

      glBindBuffer(GL_ARRAY_BUFFER, this->_buf);
      glEnableVertexAttribArray(loc);
      glVertexAttribPointer(loc, this->_attribute.getSize(), this->_attribute.getType(), GL_FALSE, 0, BUFFER_OFFSET(0));
    }
  }

  bool hasBeenUploaded() const {
    return _uploaded;
  }

protected:
  bool _uploaded;
  Attribute _attribute;
};

template <>
inline void AttributeBuffer<glm::mat4>::bind(const Pointer<Shader>& shader) {
  if (this->_vector.size() > 0) {
    const GLuint loc = shader->getAttribute(this->_attribute.getName());

    glBindBuffer(GL_ARRAY_BUFFER, this->_buf);

    glEnableVertexAttribArray(loc);
    glEnableVertexAttribArray(loc+1);
    glEnableVertexAttribArray(loc+2);
    glEnableVertexAttribArray(loc+3);

    GLsizei stride = sizeof(glm::mat4);
    GLsizei offset = sizeof(glm::vec4);

    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(offset * 0));
    glVertexAttribPointer(loc+1, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(offset * 1));
    glVertexAttribPointer(loc+2, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(offset * 2));
    glVertexAttribPointer(loc+3, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(offset * 3));

    glVertexAttribDivisor(loc, 1);
    glVertexAttribDivisor(loc+1, 1);
    glVertexAttribDivisor(loc+2, 1);
    glVertexAttribDivisor(loc+3, 1);
  }
}

} /* buffers */
} /* graphics */
} /* hx3d */
