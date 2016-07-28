#include "tests/screens/base_test_screen.hpp"

#include "hx3d/hx3d.hpp"

using namespace hx3d;
using namespace hx3d::graphics;

class Test20: public BaseTestScreen {
public:
  Test20();

  virtual void update(float delta) override;
  virtual void render() override;

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch::Ref batch;
  Skeleton::Ptr skel;
};
