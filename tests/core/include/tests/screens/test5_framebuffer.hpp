#include "./base_test_screen.hpp"

#include "hx3d/ecs/engine.hpp"
#include "hx3d/ecs/component.hpp"
#include "hx3d/ecs/system.hpp"
#include "hx3d/ecs/entity.hpp"

#include "hx3d/math/number_utils.hpp"
#include "hx3d/graphics/font.hpp"
#include "hx3d/graphics/text.hpp"

using namespace hx3d;

class Test5: public BaseTestScreen {
public:
  Test5():
    baseShader(Core::Assets()->get<Shader>("base")),
    pixShader(Core::Assets()->get<Shader>("pix2D"))
  {
    batch->setCamera(camera);

    sprite->setTexture(Core::Assets()->get<Texture>("box"));
    sprite->transform.size = glm::vec3(64);
    sprite->transform.position = glm::vec3(Core::App()->getWidth() / 2 - 64 / 2, Core::App()->getHeight() / 2 - 64 / 2, 0);
    sprite->setTint(Color::White);

    glm::vec2 screenSize = Core::App()->getSize();
    framebufferSprite->setTexture(framebuffer);
    framebufferSprite->transform.position = glm::vec3(
      screenSize.x / 2,
      screenSize.y / 2,
      0
    );

    text->setContent("WOOOOOOOOOHOOOOOOOOO !!");
    text->transform.position = glm::vec3(
      Core::App()->getWidth() / 2,
      Core::App()->getHeight() / 2 - 200,
      0
    );
    text->setFunction(math::Function(0, 0.5f, [](float& x, float& y, float t) {
      y = std::sin(t) * 5.f;
    }));
  }

  virtual void update(float delta) override {
    camera->update();

    float angle = framebufferSprite->transform.rotation.z;
    angle += glm::radians(1.f);

    angle = math::mclamp(angle, 0.f, 360.f);
    framebufferSprite->transform.rotation.z = angle;

    text->setFunctionInit(Core::App()->getElapsedTime() * 2);
  }

  virtual void render() override {

    Framebuffer::push(framebuffer);
    Framebuffer::clear(Color::Black);

    batch->begin();
    batch->draw(sprite);
    batch->draw(text);
    batch->end();

    Framebuffer::pop();
    Framebuffer::clear(Color::Black);

    Shader::use(pixShader);
    pixShader->setUniform1f("time", Core::App()->getElapsedTime());
    pixShader->setUniform2f("resolution", Core::App()->getSize());
    pixShader->setUniform2f("pixel_size", glm::vec2(10.f, 10.f));
    Shader::disable();

    batch->setShader(pixShader);

    batch->begin();
    batch->draw(framebufferSprite);
    batch->end();

    batch->setShader(baseShader);
  }

private:
  Shader::Ptr baseShader;
  Shader::Ptr pixShader;

  Framebuffer::Ref framebuffer;
  OrthographicCamera::Ref camera;

  Text::Ref text;

  SimpleBatch::Ref batch;
  Sprite::Ref sprite;
  Sprite::Ref framebufferSprite;
};
