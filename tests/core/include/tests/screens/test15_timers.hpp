#include "./base_test_screen.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/utils/timer_manager.hpp"

#include "hx3d/utils/callback_timer.hpp"

using namespace hx3d;

class Test15: public BaseTestScreen {
public:
  Test15()
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    sprite.setTexture(Core::Assets()->get<Texture>("box"));
    sprite.transform.position.x = Core::App()->getWidth() / 2;
    sprite.transform.position.y = Core::App()->getHeight() / 2;

    timers.createNamedTimer("base", 2000, [](){
      Log.Info("Base timer end !");
    });

    timers.createNamedTimer("two", 3000, [](){
      Log.Info("Two timer end !");
    });

    timers.createTemporaryTimer(4000, [](){
      Log.Info("Temp timer end !");
    });
  }

  virtual void update(float delta) override {
    timers.update(delta);
  }

  virtual void render() override {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    batch.draw(sprite);

    batch.end();
  }

private:
  OrthographicCamera camera;
  TimerManager timers;

  Sprite sprite;
  Batch batch;
};
