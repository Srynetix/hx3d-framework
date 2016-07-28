#pragma once

#include "tests/screens/base_test_screen.hpp"

#include "hx3d/graphics/cameras/perspective_camera.hpp"
#include "hx3d/graphics/batches/simple_batch.hpp"
#include "hx3d/graphics/mesh.hpp"
#include "hx3d/graphics/sprite.hpp"

using namespace hx3d;
using namespace hx3d::window;
using namespace hx3d::graphics;

class Test1: public BaseTestScreen {
public:
  Test1();

  virtual void update(float delta) override;
  virtual void render() override;

private:
  PerspectiveCamera::Ref camera;
  SimpleBatch::Ref batch;

  Mesh::Ref cube;
  Mesh::Ref star;

  Sprite::Ref sprite;
  float angle;
};
