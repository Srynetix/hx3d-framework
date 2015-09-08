#include "./base_test_screen.hpp"

#include "hx3d/math/random.hpp"
#include "hx3d/math/vector_utils.hpp"

#include "hx3d/core/events.hpp"

#include "hx3d/utils/timer.hpp"

#include "hx3d/audio/audio.hpp"
#include "hx3d/audio/music.hpp"
#include "hx3d/audio/display/waveform.hpp"
#include "hx3d/audio/display/spectrum.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

using namespace hx3d;

class Test7: public BaseTestScreen {
public:
  Test7():
    music("sounds/music.mp3"),
    text(Core::Assets()->get<Font>("default")),
    fps(Core::Assets()->get<Font>("default")),
    stream(nullptr),
    len(0)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    waveform.create(256, 256);
    waveform.setRefreshDelay(16);
    spectrum.create(256, 256);
    spectrum.setRefreshDelay(16);

    musicToggle = false;
    process = false;

    text.transform.position.x = 20;
    text.transform.position.y = 20;

    fps.setContent("FPS:");
    fps.transform.position.x = 20;
    fps.transform.position.y = Core::App()->getHeight() - 20;

    waveformSprite.setTexture(waveform.getTexture());
    waveformSprite.transform.position.x = Core::App()->getWidth() / 4;
    waveformSprite.transform.position.y = Core::App()->getHeight() / 2;

    spectrumSprite.setTexture(spectrum.getTexture());
    spectrumSprite.transform.position.x = Core::App()->getWidth() / 1.5f;
    spectrumSprite.transform.position.y = Core::App()->getHeight() / 2;

    Mix_RegisterEffect(MIX_CHANNEL_POST, effect, nullptr, this);
  }

  static void effect(int channel, void* stream, int len, void *udata) {
    Test7* me = (Test7*)udata;

    if (!me->stream)
      me->stream = new Sint16[len/2];
    me->len = len/2;

    Sint8* str = (Sint8*)stream;
    for (int i = 0; i < len; i += 2) {
      Sint8 a = str[i+1];
      Sint8 b = str[i];
      Uint8 ua = a < 0 ? 127 - a : a;
      Uint8 ub = b < 0 ? 127 - b : b;
      Uint16 us = (ua << 8 | ub);
      Sint16 s = us > 32767 ? -(us - 32767) : us;

      me->stream[i/2] = s;
    }

    me->process = true;
  }

  void update() {
    camera.update();

    text.setContent(format("Music played: %s", music.isPlaying() ? "On" : "Off"));
    fps.setContent(format("FPS: %2.2f", Core::App()->getFPS()));

    if (Core::Events()->isScreenJustTouched()) {
      if (!musicToggle)
        music.play();
      else
        music.stop();

      musicToggle = !musicToggle;
    }

    if (process) {
      waveform.update(stream, len);
      spectrum.update(stream, len);
      process = false;
    }
  }

  void render() {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    batch.draw(waveformSprite);
    batch.draw(spectrumSprite);

    batch.draw(text);
    batch.draw(fps);

    batch.end();
  }

  void hide() {
    Mix_UnregisterEffect(MIX_CHANNEL_POST, effect);
  }

private:
  Ptr<Texture> texture;

  OrthographicCamera camera;
  audio::Music music;
  audio::Waveform waveform;
  audio::Spectrum spectrum;

  Sprite spectrumSprite;
  Sprite waveformSprite;
  gui::Text text;
  gui::Text fps;

  bool musicToggle;
  bool process;

  Timer timer;

  Sint16* stream;
  int len;

  Batch batch;
};
