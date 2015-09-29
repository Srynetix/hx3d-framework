#include "./base_test_screen.hpp"

#include "hx3d/math/random.hpp"
#include "hx3d/math/number_utils.hpp"

#include "hx3d/utils/callback_timer.hpp"

#include "hx3d/core/events.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

using namespace hx3d;

class Test8: public BaseTestScreen {
public:
  Test8():
    count(0)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    /* Image */
    image.create(200, 200);

    image.setRect(0, 0, 200, 1, Color::White);
    image.setRect(0, 199, 200, 1, Color::White);
    image.setRect(0, 0, 1, 200, Color::White);
    image.setRect(199, 0, 1, 200, Color::White);
    image.buildTexture();

    sprite.setTexture(image.getTexture());
    sprite.transform.position.x = Core::App()->getWidth() / 2;
    sprite.transform.position.y = Core::App()->getHeight() / 2;

    image.setRect(10, 10, 10, 10, Color::Red);
    image.setRect(20, 20, 10, 10, Color::Green);
    image.setRect(30, 30, 10, 10, Color::Blue);

    image.setRect(50, 50, 100, 100, Color::White);

    image.updateTextureZone(0, 0, 200, 200);

    timer.initialize(1000, [this](){
      Color color =
        count == 0 ? Color::Red :
        count == 1 ? Color::Green :
        Color::Blue;

      image.setRect(50, 50, 100, 100, color);
      image.updateTextureZone(50, 50, 100, 100);

      count = math::mclamp(count+1, 0, 3);
      timer.reset();
    });
  }

  virtual void update(float delta) override {
    timer.update(delta);
    camera.update();

    sprite.transform.rotation.z = glm::radians(angle);

    angle = math::mclamp(angle + 1, 0, 360);
  }

  void render() {
    Framebuffer::clear(Color::Black);

    batch.begin();

    for (int i = 0; i < 3; ++i) {
      sprite.transform.position.x = 220 + i * 350;
      batch.draw(sprite);
    }

    batch.end();
  }

private:
  OrthographicCamera camera;

  Image image;
  Sprite sprite;
  Batch batch;
  CallbackTimer timer;

  float angle;
  int count;
};
