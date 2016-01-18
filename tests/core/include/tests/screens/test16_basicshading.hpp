#include "./base_test_screen.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/geometries/sprite_geometry.hpp"
#include "hx3d/utils/timer_manager.hpp"

#include "hx3d/utils/callback_timer.hpp"

using namespace hx3d;

class Test16: public BaseTestScreen {
public:
  Test16(): camera(0.1f, 100.f)
  {
    camera.translate(glm::vec3(0.f, 0.f, -5.f));
    camera.rotate(180.f, glm::vec3(0, 1, 0));

    batch.setShader(Core::Assets()->get<Shader>("light3D"));
    batch.setCamera(camera);

    auto geo = std::dynamic_pointer_cast<geom::SpriteGeometry>(sprite.getGeometry());
    geo->setAttribute("Normal", std::vector<float> {
      0.f, 0.f, 1.f,
      0.f, 0.f, 1.f,
      0.f, 0.f, 1.f,
      0.f, 0.f, 1.f
    });
    geo->setFaceCulling(Culling::Disabled);
    geo->uploadAll();

    sprite.setTexture(Core::Assets()->get<Texture>("box"));

    sprite.transform.size = glm::vec3(2.f);

    sprite.transform.position.x = 0;
    sprite.transform.position.y = 0;
    sprite.transform.position.z = 0;
    sprite.transform.rotation.y = glm::radians(180.f);

    auto shader = batch.getShader();
    Shader::use(shader);
    shader->setUniform3f("light.position", glm::vec3(0, 0, -0.5));
    shader->setUniform3f("light.color", glm::vec3(0.5f, 1.f, 0.5f));
    shader->setUniform3f("light.specular", glm::vec3(0.2f, 0.2f, 0.2f));
    shader->setUniform3f("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    shader->setUniform1f("light.power", 3);
    Shader::disable();

    angle = 180.f;
  }

  virtual void update(float delta) override {
    camera.update();

    angle = math::mclamp(angle + 1, 0.f, 360.f);
  }

  virtual void render() override {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    sprite.transform.rotation.y = glm::radians(angle);

    batch.draw(sprite);
    batch.end();
  }

private:
  PerspectiveCamera camera;

  Sprite sprite;
  Batch batch;
  float angle;
};
