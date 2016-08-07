#pragma once

#include "tests/screens/base_test_screen.hpp"

#include "hx3d/hx3d.hpp"
#include "hx3d/graphics/drawers/mesh_drawer.hpp"

#include <glm/gtc/type_ptr.hpp>

using namespace hx3d;
using namespace hx3d::graphics;

class Transform2D {
public:
  Transform2D():
    _dirty(true),
    _lastCompute(1.f),
    _position(0.f),
    _size(1.f),
    _scale(1.f),
    _r(0.f)
    {}

  glm::mat4 compute() {
    if (_dirty) {
      _lastCompute = glm::mat4(1.f);
      _lastCompute = glm::translate(_lastCompute, glm::vec3(_position.x, _position.y, 0));
      _lastCompute = glm::rotate(_lastCompute, _r, glm::vec3(0, 0, 1));
      _lastCompute = glm::scale(_lastCompute, glm::vec3(_size.x, _size.y, 0));
      _lastCompute = glm::scale(_lastCompute, glm::vec3(_scale.x, _scale.y, 0));

      _dirty = false;
    }

    return _lastCompute;
  }

  void setPosition(float x, float y) {
    if (x == _position.x && y == _position.y) return;

    _position = {x, y};
    _dirty = true;
  }

  void setRotation(float r) {
    if (r == _r) return;

    _r = r;
    _dirty = true;
  }

  void setScale(float sx, float sy) {
    if (sx == _scale.x && sy == _scale.y) return;

    _scale = {sx, sy};
    _dirty = true;
  }

  void setSize(float w, float h) {
    if (w == _size.x && h == _size.y) return;

    _size = {w, h};
    _dirty = true;
  }

  void resize(float w, float h) {
    if (w == 0 && h == 0) return;
    setSize(_size.x + w, _size.y + h);
  }

  void move(float x, float y) {
    if (x == 0 && y == 0) return;
    setPosition(_position.x + x, _position.y + y);
  }

  void scale(float sx, float sy) {
    if (sx == 0 && sy == 0) return;
    setScale(_scale.x + sx, _scale.y + sy);
  }

  void rotate(float r) {
    if (r == 0) return;
    setRotation(r);
  }

  glm::vec2 getPosition() const {
    return _position;
  }

  glm::vec2 getSize() const {
    return _size;
  }

  glm::vec2 getScale() const {
    return _scale;
  }

  float getRotation() const {
    return _r;
  }

  bool isDirty() const {
    return _dirty;
  }

private:
  bool _dirty;

  glm::mat4 _lastCompute;

  glm::vec2 _position;
  glm::vec2 _size;
  glm::vec2 _scale;
  float _r;
};

class FastSpriteGeometry: public SpriteGeometry {
public:
  FastSpriteGeometry(): SpriteGeometry()
  {
    this->addAttribute("Model", Attribute("a_model", GL_FLOAT, 16));
    this->uploadAll();
  }

  void updateModel(const Pointer<Transform2D>& transf) {
    if (transf->isDirty() || this->getAttribute("Model").size() == 0) {

      VertexArray::use(this->getVertexArray());

      // Update model
      auto mat = transf->compute();

      this->setAttribute("Model", std::vector<float> {
        mat[0][0], mat[1][0], mat[2][0], mat[3][0],
        mat[0][1], mat[1][1], mat[2][1], mat[3][1],
        mat[0][2], mat[1][2], mat[2][2], mat[3][2],
        mat[0][3], mat[1][3], mat[2][3], mat[3][3],
      });

      this->getAttribute("Model").upload();

      VertexArray::disable();
    }
  }
};

class FastSpriteDrawer: public MeshDrawer {
public:
  FastSpriteDrawer(): MeshDrawer() {}

  virtual void drawWithShader(const Pointer<Geometry>& geom, const Pointer<Shader>& shader) override {
    switch (geom->getFaceCulling()) {
      case Culling::Disabled:
        glDisable(GL_CULL_FACE);
        break;
      case Culling::Front:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        break;
      case Culling::Back:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        break;
    }

    VertexArray::use(geom->getVertexArray());

    // Begin

    for (auto& attr_pair: geom->getAttributes()) {
      if (attr_pair.first != "Model") {
        attr_pair.second.begin(shader);
      }
    }

    // Model
    auto& model = geom->getAttribute("Model");
    auto model_attr = model.getAttribute();
    const GLint loc = shader->getAttribute(model_attr.getName());

    glEnableVertexAttribArray(loc);
    glEnableVertexAttribArray(loc+1);
    glEnableVertexAttribArray(loc+2);
    glEnableVertexAttribArray(loc+3);

    glBindBuffer(GL_ARRAY_BUFFER, model.getId());

    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(0));
    glVertexAttribPointer(loc+1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 4));
    glVertexAttribPointer(loc+2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 8));
    glVertexAttribPointer(loc+3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 12));

    auto& indices = geom->getIndices();
    if (indices.size() > 0) {
      indices.begin(shader);
      indices.end(shader);
    }

//    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0, 1);

    // End

    for (auto& attr_pair: geom->getAttributes()) {
      if (attr_pair.first != "Model") {
        attr_pair.second.end(shader);
      }
    }

    glDisableVertexAttribArray(loc);
    glDisableVertexAttribArray(loc+1);
    glDisableVertexAttribArray(loc+2);
    glDisableVertexAttribArray(loc+3);

    VertexArray::disable();
  }
};

class Mesh2D: public Transform2D {
public:
  Mesh2D() {
    _geoDrawer = Make<MeshDrawer>();
  }

  void draw(const Pointer<Shader>& shader) {
    if (!_geometry || !_geoDrawer) {
      return;
    }

    if (_geometry->getAttribute("Texture").size() == 0) {
      Texture::use(Texture::Blank);
      _geoDrawer->drawWithShader(_geometry, shader);
      Texture::disable();
    }

    else {
      _geoDrawer->drawWithShader(_geometry, shader);
    }
  }

  void setGeometryDrawer(const Pointer<GeometryDrawer>& drawer) {
    _geoDrawer = drawer;
  }

  void setGeometry(const Pointer<Geometry>& geometry) {
    _geometry = geometry;
  }

private:
  Pointer<Geometry> _geometry;
  Pointer<GeometryDrawer> _geoDrawer;
};

class Test3: public BaseTestScreen {
public:
  Test3();
  virtual void update(float delta) override;
  virtual void render() override;

private:
  Pointer<Shader> shader;
  OrthographicCamera::Ref camera;
  std::vector<Pointer<Mesh2D>> meshes;

  float angle;
};
