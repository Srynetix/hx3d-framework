#include "tests/screens/base_test_screen.hpp"

#include "hx3d/graphics/cameras/orthographic_camera.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/batches/simple_batch_2d.hpp"
#include "hx3d/gui/system.hpp"

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::gui;

class Test22: public BaseTestScreen {
public:
  Test22();

  virtual void update(float delta) override;
  virtual void render() override;

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch2D::Ref batch;
  System::Ptr system;
};
