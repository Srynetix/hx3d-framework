#include "./base_test_screen.hpp"

#include "hx3d/math/random.hpp"
#include "hx3d/math/vector_utils.hpp"

#include "hx3d/core/events.hpp"

#include "hx3d/utils/timer.hpp"

#include "hx3d/audio/audio.hpp"
#include "hx3d/audio/music.hpp"

using namespace hx3d;

class Test7: public BaseTestScreen {
public:
  Test7():
    music("sounds/test.ogg"),
    text(Core::Assets()->get<Font>("default"))
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    musicToggle = false;

    Mix_SetPostMix([](void* udata, Uint8* stream, int len) {
      Test7* me = (Test7*)udata;
    }, this);

    text.transform.position.x = 20;
    text.transform.position.y = 20;
  }

  void update() {
    camera.update();

    text.setContent(format("Music played: %s", musicToggle ? "On" : "Off"));

    if (Core::Events()->isScreenJustTouched()) {
      if (!musicToggle)
        music.play();
      else
        music.stop();

      musicToggle = !musicToggle;
    }
  }

  void render() {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    batch.draw(text);

    batch.end();
  }

private:
  OrthographicCamera camera;
  Music music;

  gui::Text text;

  bool musicToggle;

  Batch batch;
};
