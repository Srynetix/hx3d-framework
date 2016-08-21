#pragma once

#include "tests/screens/base_test_screen.hpp"

#include "hx3d/hx3d.hpp"
#include "hx3d/graphics/drawers/mesh_drawer.hpp"

#include <glm/gtc/type_ptr.hpp>

using namespace hx3d;
using namespace hx3d::graphics;

class SpriteBatch {
public:
  SpriteBatch(unsigned int max_sprites):
    _positions(Attribute("a_position", GL_FLOAT, 3)),
    _colors(Attribute("a_color", GL_FLOAT, 4)),
    _textures(Attribute("a_texture", GL_FLOAT, 2)),
    _matrices(Attribute("a_model", GL_FLOAT, 16)),
    _lastId(0),
    _maxSprites(max_sprites)
    {
      // Prepare base geometry
      _positions.set(std::vector<float> {
        -0.5f, 0.5f, 0.f,
        0.5, 0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        -0.5f, -0.5f, 0.f
      });

      _indices.set(std::vector<unsigned short> {
        0, 2, 1,
        0, 3, 2
      });

      _positions.upload(GL_STATIC_DRAW);
      _indices.upload(GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, _colors.getId());
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * max_sprites, _colors.data(), GL_STREAM_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, _textures.getId());
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4 * max_sprites, _textures.data(), GL_STREAM_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, _matrices.getId());
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16 * max_sprites, _matrices.data(), GL_STREAM_DRAW);
    }

  void setShader(const Pointer<Shader>& shader) {
    _shader = shader;
  }

  void setTexture(const Pointer<Texture>& texture) {
    _texture = texture;
  }

  void render() {
    Shader::use(_shader);
    Texture::use(_texture);

    // Bind
    _bind();

    // Draw
    _draw();

    Texture::disable();
  }

  void erase(const Pointer<Mesh>& mesh) {
    auto search = _lut.find(mesh);
    if (search != _lut.end()) {
      unsigned int id = search->second;

      auto m0 = glm::mat4(0);
      glBindBuffer(GL_ARRAY_BUFFER, _matrices.getId());
      glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 16 * id, sizeof(float) * 16, &m0);

      _lut.erase(mesh);
    }
  }

  void draw(const Pointer<Mesh>& mesh) {
    auto search = _lut.find(mesh);
    if (search != _lut.end()) {
      auto& geo = mesh->getGeometry();
      unsigned int id = search->second;

      if (mesh->isDirty()) {
        auto mat = mesh->compute();

        glBindBuffer(GL_ARRAY_BUFFER, _matrices.getId());
        glBufferSubData(GL_ARRAY_BUFFER, id * sizeof(float) * 16, sizeof(float) * 16, &mat);
      }

      if (mesh->hasColorChanged()) {
        auto& mCols = geo->getAttributeBuffer("Color");

        glBindBuffer(GL_ARRAY_BUFFER, _colors.getId());
        glBufferSubData(GL_ARRAY_BUFFER, id * sizeof(float) * 4, sizeof(float) * 4, mCols.data());
      }
    }

    else {
      unsigned int id = 0;
      if (_freeIds.size() > 0) {
        id = _freeIds.front();
        _freeIds.pop();
      } else {
        id = _lastId++;
      }

      _lut[mesh] = id;

      // Store values

      // Colors
      auto& mCols = mesh->getGeometry()->getAttributeBuffer("Color");
      for (int i = 0; i < 4; ++i) {
        _colors.add(mCols.getValue(i));
      }

      glBindBuffer(GL_ARRAY_BUFFER, _colors.getId());
      glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 4 * id, sizeof(float) * 4, mCols.data());

      // Textures
      auto& mTexs = mesh->getGeometry()->getAttributeBuffer("Texture");
      _textures.add(mTexs.getVector());

      glBindBuffer(GL_ARRAY_BUFFER, _textures.getId());
      glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4 * id, sizeof(float) * 2 * 4, mTexs.data());

      // Matrices
      auto mat = mesh->compute();
      _matrices.add(mat);

      glBindBuffer(GL_ARRAY_BUFFER, _matrices.getId());
      glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * id, sizeof(glm::mat4), &mat);
    }
  }

  void _draw() {
    VertexArray::use(_array);
    glDrawElementsInstanced(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_SHORT, BUFFER_OFFSET(0), _lastId);
    VertexArray::disable();
  }

  void _bind() {
    VertexArray::use(_array);

    _positions.bind(_shader);
    _textures.bind(_shader);
    _indices.bind();

    _colors.bind(_shader);
    _matrices.bind(_shader);

    glVertexAttribDivisor(_shader->getAttribute("a_color"), 1);

    VertexArray::disable();
  }

  Pointer<Shader> _shader;

  std::map<Pointer<Mesh>, unsigned int> _lut;
  std::queue<unsigned int> _freeIds;
  std::vector<unsigned int> _dirtied;
  Pointer<Texture> _texture;

  VertexArray _array;
  AttributeBuffer<float> _positions;
  AttributeBuffer<float> _colors;
  AttributeBuffer<float> _textures;
  AttributeBuffer<glm::mat4> _matrices;

  IndexBuffer<unsigned short> _indices;

  unsigned int _lastId;
  unsigned int _maxSprites;
};

class Test3: public BaseTestScreen {
public:
  Test3();
  virtual void update(float delta) override;
  virtual void render() override;

private:
  Pointer<Shader> shader;
  OrthographicCamera::Ref camera;
  Pointer<SpriteBatch> spBatch;

  std::vector<Pointer<Mesh>> meshes;

  float angle;
};
