#include "./base_test_screen.hpp"

#include "hx3d/graphics/geometries/cube_geometry.hpp"
#include "hx3d/graphics/geometries/star_geometry.hpp"

class Test1: public BaseTestScreen {
public:
  Test1():
    camera(0.1f, 100.f)
  {
    camera.translate(glm::vec3(0.f, 0.f, -5.f));
    camera.rotate(180.f, glm::vec3(0, 1, 0));
    camera.update();

    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    sprite.setTexture(Core::Assets()->get<Texture>("box"));
    sprite.getGeometry()->setFaceCulling(Culling::Disabled);

    cube.setGeometry(Make<geom::CubeGeometry>());
    star.setGeometry(Make<geom::StarGeometry>());

    angle = 0.f;
  }

  virtual void update(float delta) override {
    camera.rotateAround(glm::vec3(0.f, 0.f, 0.f), 1.f, glm::vec3(0, 1, 0));
    camera.update();
  }

  virtual void render() override {
    static float angle = 0.f;

    Framebuffer::clear(Color::Black);

    batch.begin();

    sprite.transform.size = glm::vec3(0.25f);

    sprite.transform.position.z = -1.5f;
    for (int j = 0; j < 12; ++j) {
      sprite.transform.position.y = 1.5f - (0.25f * j);

      for (int i = 0; i < 12; ++i) {
        sprite.transform.position.x = -1.5f + (0.25f * i);
        sprite.transform.rotation.y = (j + i) * 2 + glm::radians(angle);
        batch.draw(sprite);
      }
    }

    sprite.transform.position.z = 1.5f;
    for (int j = 0; j < 12; ++j) {
      sprite.transform.position.y = 1.5f - (0.25f * j);

      for (int i = 0; i < 12; ++i) {
        sprite.transform.position.x = -1.5f + (0.25f * i);
        sprite.transform.rotation.y = (j + i) * 2 + glm::radians(angle);
        batch.draw(sprite);
      }
    }

    star.transform.size = glm::vec3(0.3f);
    star.transform.position.x = 0;
    star.transform.position.y = 0;
    star.transform.position.z = 0;
    star.transform.rotation.y = glm::radians(angle * 2);
    batch.draw(star);

    star.transform.size = glm::vec3(0.1f);
    star.transform.rotation.y = glm::radians(-angle * 4);

    star.transform.position.x = -0.75f;
    batch.draw(star);

    star.transform.position.x = 0.f;
    star.transform.position.z = -0.75f;
    batch.draw(star);

    star.transform.position.x = 0.75f;
    star.transform.position.z = 0.f;
    batch.draw(star);

    star.transform.position.x = 0;
    star.transform.position.z = 0.75f;
    batch.draw(star);

    star.transform.position.y = 0.75f;
    star.transform.position.z = 0;
    batch.draw(star);

    star.transform.position.y = -0.75f;
    batch.draw(star);

    angle += 2.f;
    if (angle > 360.f) {
      angle -= 360.f;
    }

    batch.end();
  }

private:
  PerspectiveCamera camera;
  Batch batch;

  Mesh cube;
  Mesh star;

  Sprite sprite;

  float angle;
};
