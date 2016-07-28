#include "tests/screens/test20_skeleton.hpp"

Test20::Test20()
{
  Core::Assets()->create<Skeleton>("skel", "skeletons/chara/joints.yml");

  skel = Core::Assets()->get<Skeleton>("skel");
  skel->setPosition(Core::App()->getWidth() / 2, Core::App()->getHeight() / 2);
  skel->rotateJoint("body", 45);
  skel->rotateJoint("l-uleg", 45);
  skel->rotateJoint("r-sho", 45);

  batch->setCamera(camera);
}

void Test20::update(float delta) {
  camera->update();

  skel->rotateRoot(1);
}

void Test20::render() {
  Framebuffer::clear(Color::Black);

  batch->begin();
  skel->draw(batch);
  batch->end();
}
