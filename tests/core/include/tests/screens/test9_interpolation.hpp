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
    baseXs.resize(count);
    texts.reserve(count);

    unsigned int appW = Core::App()->getWidth();
    unsigned int appH = Core::App()->getHeight();

    caseW = appW / 9.f;
    caseH = appH / 8.f;
    duration = 2.5f;

    for (unsigned int i = 0; i < count; ++i) {
      texts.emplace_back(Core::Assets()->get<Font>("default"));

      if (i == count - 1) {
        math::Interpolation interp = math::Interpolation::Linear;
        buildBox(count-1, appW / 2.f, appH / 2.f, caseW, caseH, interp);
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
    Sprite& sprite = sprites[i];
    gui::Text& text = texts[i];

    baseXs[i] = x;

    text.setContent(getInterpName(interp));

    sprite.setTexture(Core::Assets()->get<Texture>("box"));
    sprite.transform.size.x = w / 4;
    sprite.transform.size.y = h / 2;

    sprite.transform.position.x = x;
    sprite.transform.position.y = y;

    text.transform.position.x = x - w/2;
    text.transform.position.y = y - h/2 - 20;
  }

  void moveBox(unsigned int i, unsigned int baseX, unsigned int endX, math::Interpolation inter) {
    Sprite& sprite = sprites[i];

    if (currentTime < duration) {
      float pos = math::interpolate(baseX, endX, currentTime/duration, inter);
      sprite.transform.position.x = pos;
    } else {
      sprite.transform.position.x = baseX;
    }
  }

  void update() {
    camera.update();

    for (unsigned int i = 0; i < sprites.size(); ++i) {
      math::Interpolation interp = math::Interpolation::Linear;
      if (i != sprites.size() - 1) {
        interp = static_cast<math::Interpolation>(i + 1);
      }

      moveBox(i, baseXs[i] - 50, baseXs[i] + 50, interp);
    }

    currentTime += 1.f/60.f;
    if (currentTime > duration)
      currentTime = 0.f;
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

    batch.end();
  }

private:
  OrthographicCamera camera;

  std::vector<Image> images;
  std::vector<Sprite> sprites;
  std::vector<float> baseXs;
  std::vector<gui::Text> texts;

  Batch batch;

  float currentTime;
  float angle;
  float caseW;
  float caseH;
  float duration;
};
