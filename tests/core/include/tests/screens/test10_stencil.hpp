#include "./base_test_screen.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"
#include "hx3d/graphics/stencil.hpp"

using namespace hx3d;

class Test10: public BaseTestScreen {
public:
  Test10():
    text(Core::Assets()->get<Font>("default"))
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    sprite.setTexture(Core::Assets()->get<Texture>("box"));
    sprite.transform.position.x = Core::App()->getWidth() / 2;
    sprite.transform.position.y = Core::App()->getHeight() / 2;

    stencilSprite.setTexture(Core::Assets()->get<Texture>("box"));
    stencilSprite.transform = sprite.transform;

    text.setContent("Hey !");
    text.transform.position = sprite.transform.position;
    text.transform.position.z = 0.5f;

    stencil.enable();
    stencil.setFunction(
      Stencil::Function::Never,
      1,
      0xFF
    );

    stencil.setOperation(
        Stencil::Operation::Replace,
        Stencil::Operation::Keep,
        Stencil::Operation::Keep
    );

    angle = 0.f;
  }

  virtual void hide() override {
    stencil.disable();
  }

  virtual void update(float delta) override {
    camera.update();

    sprite.transform.rotation.z = glm::radians(angle);
    stencilSprite.transform.scale = glm::vec3(1.f - 0.5f * std::abs(std::sin(glm::radians(angle))));

    angle = math::mclamp(angle + 1, 0, 360);
  }

  virtual void render() override {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    stencil.begin();
    batch.draw(stencilSprite);
    stencil.end();

    batch.draw(sprite);

    batch.draw(text, math::Function(Core::App()->getElapsedTime() * 2, 0.5f, [](float& x, float& y, float t) {
      y = std::sin(t) * 5.f;
    }));

    batch.end();
  }

private:
  OrthographicCamera camera;

  Stencil stencil;
  Sprite sprite;
  Sprite stencilSprite;
  gui::Text text;

  Batch batch;

  float angle;
};
