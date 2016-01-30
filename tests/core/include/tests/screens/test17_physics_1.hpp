#include "./base_test_screen.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"

#include "hx3d/physics/2d/world.hpp"
#include "hx3d/physics/2d/collider.hpp"

using namespace hx3d;

class Test17: public BaseTestScreen {
public:
  Test17()
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    sprite.setTexture(Core::Assets()->get<Texture>("box"));
    sprite.transform.position.x = Core::App()->getWidth() / 2;
    sprite.transform.position.y = Core::App()->getHeight() / 2;

    auto physRatio = world.getPhysRatio();

    auto poly = Make<physics2d::colliders::Polygon>(physics2d::Collider::Type::Static);
    poly->setAsBox(Core::App()->getWidth() / physRatio, 50 / physRatio);
    poly->position.x = (Core::App()->getWidth() / 2) / physRatio;
    poly->position.y = 0;

    auto me = Make<physics2d::colliders::Polygon>(physics2d::Collider::Type::Dynamic);
    me->setAsBox(50 / physRatio, 50 / physRatio);
    me->position.x = 100 / physRatio;
    me->position.y = 500 / physRatio;

    world.addCollider(poly);
    world.addCollider(me);
  }

  virtual void update(float delta) override {
    world.step(delta);
  }

  virtual void render() override {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    world.render(batch);

    batch.end();
  }

private:
  OrthographicCamera camera;
  physics2d::World world;

  Sprite sprite;
  Batch batch;
};
