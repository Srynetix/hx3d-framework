#include "./base_test_screen.hpp"

#include "hx3d/core/events.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

#include "hx3d/utils/chronometer.hpp"

using namespace hx3d;

class Test9: public BaseTestScreen {
public:
  Test9()
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    unsigned int count = 31;
    images.resize(count);
    sprites.resize(count);
    texts.reserve(count);

    moving.setTexture(Core::Assets()->get<Texture>("box"));
    moving.transform.position.x = Core::App()->getWidth() / 4;
    moving.transform.position.y = Core::App()->getHeight() / 2;
    moving.transform.position.z = 0.5f;
    moving.transform.scale = glm::vec3(0.25f);

    unsigned int appW = Core::App()->getWidth();
    unsigned int appH = Core::App()->getHeight();

    unsigned int caseW = appW / 9.f;
    unsigned int caseH = appH / 8.f;

    for (unsigned int i = 0; i < count; ++i) {
      texts.emplace_back(Core::Assets()->get<Font>("default"));

      if (i == count - 1) {
        math::Interpolation interp = math::Interpolation::Linear;
        buildBox(count-1, appW / 2, appH / 2, caseW, caseH, interp);
      }

      else {
        math::Interpolation interp = static_cast<math::Interpolation>(i+1);
        unsigned int xIndex = i % 6;
        unsigned int yIndex = i / 6;

        unsigned int posX = xIndex < 3 ? caseW  + xIndex * caseW * 1.1f : 5.75f * caseW + (xIndex % 3) * caseW * 1.1f;
        unsigned int posY = appH - caseH - yIndex * caseH * 1.5f;

        buildBox(i, posX, posY, caseW, caseH, interp);
      }
    }

    count = 0.f;
  }

  std::string getInterpName(math::Interpolation interp) {
    return
      interp == math::Interpolation::InQuad ? "InQuad" :
      interp == math::Interpolation::OutQuad ? "OutQuad" :
      interp == math::Interpolation::InOutQuad ? "InOutQuad" :

      interp == math::Interpolation::InCubic ? "InCubic" :
      interp == math::Interpolation::OutCubic ? "OutCubic" :
      interp == math::Interpolation::InOutCubic ? "InOutCubic" :

      interp == math::Interpolation::InQuart ? "InQuart" :
      interp == math::Interpolation::OutQuart ? "OutQuart" :
      interp == math::Interpolation::InOutQuart ? "InOutQuart" :

      interp == math::Interpolation::InQuint ? "InQuint" :
      interp == math::Interpolation::OutQuint ? "OutQuint" :
      interp == math::Interpolation::InOutQuint ? "InOutQuint" :

      interp == math::Interpolation::InSine ? "InSine" :
      interp == math::Interpolation::OutSine ? "OutSine" :
      interp == math::Interpolation::InOutSine ? "InOutSine" :

      interp == math::Interpolation::InExpo ? "InExpo" :
      interp == math::Interpolation::OutExpo ? "OutExpo" :
      interp == math::Interpolation::InOutExpo ? "InOutExpo" :

      interp == math::Interpolation::InCirc ? "InCirc" :
      interp == math::Interpolation::OutCirc ? "OutCirc" :
      interp == math::Interpolation::InOutCirc ? "InOutCirc" :

      interp == math::Interpolation::InBack ? "InBack" :
      interp == math::Interpolation::OutBack ? "OutBack" :
      interp == math::Interpolation::InOutBack ? "InOutBack" :

      interp == math::Interpolation::InBounce ? "InBounce" :
      interp == math::Interpolation::OutBounce ? "OutBounce" :
      interp == math::Interpolation::InOutBounce ? "InOutBounce" :

      interp == math::Interpolation::InElastic ? "InElastic" :
      interp == math::Interpolation::OutElastic ? "OutElastic" :
      interp == math::Interpolation::InOutElastic ? "InOutElastic" :

      "Linear";
  }

  void buildBox(unsigned int i, unsigned int x, unsigned int y, unsigned int w, unsigned int h, math::Interpolation interp) {
    Image& image = images[i];
    Sprite& sprite = sprites[i];
    gui::Text& text = texts[i];

    text.setContent(getInterpName(interp));

    image.create(w, h);
    image.setRect(0, 0, w, 1, Color::White);
    image.setRect(0, h - 1, w, 1, Color::White);
    image.setRect(0, 0, 1, h, Color::White);
    image.setRect(w - 1, 0, 1, h, Color::White);

    for (unsigned int i = 0; i < image.getWidth() - 2; ++i) {
      float t = i/(float)image.getWidth();
      Color color = Color::interp(
        Color(255, 255, 0),
        Color::Red,
        t,
        interp
      );

      image.setRect(i+1, 1, 1, h - 2, color);
    }
    image.buildTexture();

    sprite.setTexture(image.getTexture());
    sprite.transform.position.x = x;
    sprite.transform.position.y = y;

    text.transform.position.x = x - w/2;
    text.transform.position.y = y - h/2 - 20;
  }

  void moveBox() {
    count += 1.f/60.f;

    if (count < 5.f) {
      float pos = math::interpolate(Core::App()->getWidth() / 4, Core::App()->getWidth() / 2 + Core::App()->getWidth() / 4, count/5.f, math::Interpolation::InElastic);

      moving.transform.position.x = pos;
    } else {
      moving.transform.position.x = Core::App()->getWidth() / 4;

      count = 0.f;
    }
  }

  void update() {
    camera.update();

    moveBox();
  }

  void render() {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();
    for (Sprite& sprite: sprites) {
      batch.draw(sprite);
    }
    for (gui::Text& text: texts) {
      batch.draw(text);
    }

    batch.draw(moving);

    batch.end();
  }

private:
  OrthographicCamera camera;

  std::vector<Image> images;
  std::vector<Sprite> sprites;
  std::vector<gui::Text> texts;

  Sprite moving;

  float count;

  Batch batch;

  float angle;
};
