#include "./base_test_screen.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

#include "hx3d/tweens/tween_manager.hpp"
#include "hx3d/tweens/sequence.hpp"
#include "hx3d/tweens/parallel.hpp"

using namespace hx3d;

class Test11: public BaseTestScreen {
public:
  Test11():
    text(Core::Assets()->get<Font>("default")),
    fps(Core::Assets()->get<Font>("default"))
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    showText = false;

    sprite.setTexture(Core::Assets()->get<Texture>("box"));
    sprite.transform.size = sprite.transform.size / 2.f;
    sprite.transform.position.x = 0;
    sprite.transform.position.y = Core::App()->getHeight() / 2;

    text.setContent("The END !");
    text.transform.position.x = Core::App()->getWidth() / 4;
    text.transform.position.y = Core::App()->getHeight() / 2;
    text.transform.position.z = 0.5f;

    fps.setContent("FPS: ");
    fps.transform.position.x = 10;
    fps.transform.position.y = Core::App()->getHeight() - 20;
    fps.transform.position.z = 0.5f;
    fps.setCenterAlignment(false);

    Pointer<tweens::Parallel> start = Make<tweens::Parallel>();
    start->addTween(sprite.transform.position.x, (float)Core::App()->getWidth() / 2.f, 10.f, math::Interpolation::OutQuad);
    start->addTween(sprite.transform.scale.x, 0.5f, 10.f, math::Interpolation::Linear);
    start->addTween(sprite.transform.scale.y, 0.5f, 10.f, math::Interpolation::Linear);
    start->addTween(sprite.transform.rotation.z, glm::radians(180.f), 10.f, math::Interpolation::InOutBounce);
    start->addTween(sprite.getTint(), Color::Green, 10.f, math::Interpolation::Linear);

    Pointer<tweens::Sequence> seq = Make<tweens::Sequence>();
    seq->add(start);
    seq->addTween(sprite.transform.position.x, 0.f, 2.5f, math::Interpolation::InOutElastic);
    seq->addCallback([this](){
      showText = true;
    });

    tweens.add(seq);
  }

  virtual void update(float delta) override {
    camera.update();
    tweens.update(delta);

    fps.setContent(format("FPS: %2.2f", 1.f/delta));
    sprite.updateColor();
  }

  virtual void render() override {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();
    batch.draw(sprite);

    batch.draw(fps);

    if (showText)
      batch.draw(text, math::Function(Core::App()->getElapsedTime() * 2, 0.5f, [](float& x, float& y, float t) {
        y = std::sin(t) * 5;
      }));

    batch.end();
  }

private:
  tweens::TweenManager tweens;
  OrthographicCamera camera;
  Sprite sprite;

  gui::Text text;
  gui::Text fps;

  Batch batch;

  bool showText;
};
