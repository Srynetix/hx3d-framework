#include "./base_test_screen.hpp"

#include "hx3d/ecs/engine.hpp"
#include "hx3d/ecs/component.hpp"
#include "hx3d/ecs/system.hpp"
#include "hx3d/ecs/entity.hpp"

#include "hx3d/math/number_utils.hpp"
#include "hx3d/graphics/font.hpp"
#include "hx3d/gui/text.hpp"

using namespace hx3d;

class Test5: public BaseTestScreen {
public:
  Test5():
    baseShader(Core::Assets()->get<Shader>("base")),
    pixShader(Core::Assets()->get<Shader>("pix2D")),
    text(Core::Assets()->get<Font>("default"))
  {
    batch.setShader(baseShader);
    batch.setCamera(camera);

    sprite.setTexture(Core::Assets()->get<Texture>("box"));
    sprite.transform.size = glm::vec3(64);
    sprite.transform.position = glm::vec3(Core::App()->getWidth() / 2 - 64 / 2, Core::App()->getHeight() / 2 - 64 / 2, 0);
    sprite.setTint(Color(255, 255, 255));

    glm::vec2 screenSize = Core::App()->getSize();
    framebufferSprite.setTexture(framebuffer);
    framebufferSprite.transform.position = glm::vec3(
      screenSize.x / 2,
      screenSize.y / 2,
      0
    );
    /*
    framebufferSprite.transform.size = glm::vec3(
      screenSize.y,
      screenSize.x,
      1
    );
    */
    // framebufferSprite.transform.rotation.z = glm::radians(90.f);

    text.setContent("WOOOOOOOOOHOOOOOOOOO !!");
    text.transform.scale = glm::vec3(2);
    text.transform.position = glm::vec3(
      Core::App()->getWidth() / 2 - 200,
      Core::App()->getHeight() / 2 - 200,
      0
    );
  }

  void update() {
    camera.update();

    float angle = framebufferSprite.transform.rotation.z;
    angle += glm::radians(1.f);

    angle = math::mclamp(angle, 0.f, 360.f);
    framebufferSprite.transform.rotation.z = angle;
  }

  void render() {

    Framebuffer::use(framebuffer);
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();
    batch.draw(sprite);
    batch.draw(text, math::Function(Core::App()->getElapsedTime() / 10.f, 0.5f, [](float& x, float& y, float t) {
      y = std::sin(t) * 5.f;
    }));
    batch.end();

    Framebuffer::useDefault();
    Framebuffer::clear(Color(0, 0, 0));

    Shader::use(pixShader);
    pixShader->setUniform1f("time", Core::App()->getElapsedTime() / 100.f);
    pixShader->setUniform2f("resolution", Core::App()->getSize());
    pixShader->setUniform2f("pixel_size", glm::vec2(10.f, 10.f));
    Shader::disable();

    batch.setShader(pixShader);

    batch.begin();
    batch.draw(framebufferSprite);
    batch.end();

    batch.setShader(baseShader);
  }

private:
  Ptr<Shader> baseShader;
  Ptr<Shader> pixShader;

  Framebuffer framebuffer;
  OrthographicCamera camera;

  gui::Text text;

  Batch batch;
  Sprite sprite;
  Sprite framebufferSprite;
};
