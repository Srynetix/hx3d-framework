#include "./base_test_screen.hpp"

using namespace hx3d;

class Test21: public BaseTestScreen {
public:
  Test21()
  {
    batch->setCamera(camera);
  }

  virtual void dispose() {
  }

  virtual void update(float delta) override {
    camera->update();
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    batch->begin();
    batch->end();
  }

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch::Ref batch;
};
