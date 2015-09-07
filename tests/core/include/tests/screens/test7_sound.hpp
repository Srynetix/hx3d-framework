#include "./base_test_screen.hpp"

#include "hx3d/math/random.hpp"
#include "hx3d/math/vector_utils.hpp"

#include "hx3d/core/events.hpp"

#include "hx3d/utils/timer.hpp"

#include "hx3d/audio/audio.hpp"
#include "hx3d/audio/music.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

using namespace hx3d;

class Test7: public BaseTestScreen {
public:
  Test7():
    music("sounds/test.ogg"),
    text(Core::Assets()->get<Font>("default")),
    fps(Core::Assets()->get<Font>("default")),
    stream(nullptr),
    len(0)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    musicToggle = false;

    Mix_SetPostMix([](void* udata, Uint8* stream, int len) {
      Test7* me = (Test7*)udata;
      me->stream = stream;
      me->len = len;
    }, this);

    text.transform.position.x = 20;
    text.transform.position.y = 20;

    fps.setContent("FPS:");
    fps.transform.position.x = 20;
    fps.transform.position.y = Core::App()->getHeight() - 20;

    /* Image */
    image.create(Core::App()->getWidth(), Core::App()->getHeight() / 2);
    image.buildTexture();

    sprite.setTexture(image.getTexture());
    sprite.transform.position.x = Core::App()->getWidth() / 2;
    sprite.transform.position.y = Core::App()->getHeight() / 2;

    timer.initialize(2);
  }

  void drawImage() {

    int w = Core::App()->getWidth();
    int h = Core::App()->getHeight() / 2;

    if (timer.isEnded()) {

      image.setRect(0, 0, w, h, Color::Black);

      if (len > 0) {
        int step = len / w;
        for (int i = 0; i < w; ++i) {
          int amp = stream[i * step];
          float norm_amp_f = amp * (h / 255.f);
          int norm_amp = norm_amp_f;

          image.setRect(i, h - norm_amp, 1, h - (h - norm_amp), Color::Red);
        }
      }

      image.updateTextureZone(0, 0, w, h);

      timer.reset();
    }
  }

  void update() {
    camera.update();

    text.setContent(format("Music played: %s", musicToggle ? "On" : "Off"));
    fps.setContent(format("FPS: %2.2f", Core::App()->getFPS()));

    if (Core::Events()->isScreenJustTouched()) {
      if (!musicToggle)
        music.play();
      else
        music.stop();

      musicToggle = !musicToggle;
    }

    drawImage();
  }

  void render() {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    batch.draw(sprite);

    batch.draw(text);
    batch.draw(fps);

    batch.end();
  }

  void hide() {
    Mix_SetPostMix(nullptr, nullptr);
  }

private:
  Ptr<Texture> texture;

  OrthographicCamera camera;
  Music music;
  Image image;

  Sprite sprite;
  gui::Text text;
  gui::Text fps;

  bool musicToggle;

  Uint8* stream;
  int len;
  Timer timer;

  Batch batch;
};
