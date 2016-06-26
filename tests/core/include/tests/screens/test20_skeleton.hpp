#include "./base_test_screen.hpp"

#include "hx3d/graphics/error.hpp"
#include "hx3d/graphics/skeletons/skeleton.hpp"

using namespace hx3d;

class Test20: public BaseTestScreen {
public:
  Test20()
  {
    // skel = Make<Skeleton>(50, 50, 0);
    // skel->setPosition(Core::App()->getWidth() / 2, Core::App()->getHeight() / 2);
    //
    // skel->addBone("head", 40, 40, 0);
    // skel->addBone("body", 70, 100, 0);
    // skel->addBone("l-leg", 30, 100, 0);
    // skel->addBone("r-leg", 30, 100, 0);
    // skel->addJoint("neck", "ROOT", "head", glm::vec2(0.5, 1), glm::vec2(0.5, 0));
    // skel->addJoint("body", "ROOT", "body", glm::vec2(0.5, 0), glm::vec2(0.5, 1));
    // skel->addJoint("l-leg", "body", "l-leg", glm::vec2(0.25, 0), glm::vec2(0.5, 1));
    // skel->addJoint("r-leg", "body", "r-leg", glm::vec2(0.75, 0), glm::vec2(0.5, 1));
    // skel->rotateRoot(90);

    Core::Assets()->create<Skeleton>("skel", "skeletons/chara/joints.yml");

    skel = Core::Assets()->get<Skeleton>("skel");
    skel->setPosition(Core::App()->getWidth() / 2, Core::App()->getHeight() / 2);
    // skel->rotateJoint("body", 45);

    batch->setCamera(camera);
  }

  virtual void dispose() {
  }

  virtual void update(float delta) override {
    camera->update();

    skel->rotateRoot(1);
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    batch->begin();
    skel->draw(batch);
    batch->end();
  }

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch::Ref batch;
  Skeleton::Ptr skel;
};
