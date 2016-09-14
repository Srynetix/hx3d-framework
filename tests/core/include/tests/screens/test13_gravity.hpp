#include "./base_test_screen.hpp"

#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/batches/simple_batch_2d.hpp"
#include "hx3d/physics/2d/world.hpp"
#include "hx3d/core/core.hpp"

#include <deque>

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::window;
using namespace hx3d::physics2d;

class Test13: public BaseTestScreen {
public:
  Test13():
    pWorld({0, -10}, 10)
  {
    batch->setCamera(camera);

    float physRatio = pWorld.getPhysRatio();

    Collider::Definition cDef;
    cDef.material.restitution = 0.f;
    cDef.material.staticFriction = 0.f;
    cDef.material.dynamicFriction = 0.f;

    auto ground = Make<Polygon>(Collider::Type::Static);
    auto top = Make<Polygon>(Collider::Type::Static);
    auto leftWall = Make<Polygon>(Collider::Type::Static);
    auto rightWall = Make<Polygon>(Collider::Type::Static);

    ground->setAsBox(Core::App()->getWidth() / physRatio, 50 / physRatio);
    ground->useDefinition(cDef);
    ground->position.x = (Core::App()->getWidth() / 2) / physRatio;
    ground->position.y = 0;

    top->setAsBox(Core::App()->getWidth() / physRatio, 50 / physRatio);
    top->useDefinition(cDef);
    top->position.x = (Core::App()->getWidth() / 2) / physRatio;
    top->position.y = Core::App()->getHeight() / physRatio;

    leftWall->setAsBox(50 / physRatio, Core::App()->getHeight() / physRatio);
    leftWall->useDefinition(cDef);
    leftWall->position.x = 0;
    leftWall->position.y = (Core::App()->getHeight() / 2) / physRatio;

    rightWall->setAsBox(50 / physRatio, Core::App()->getHeight() / physRatio);
    rightWall->useDefinition(cDef);
    rightWall->position.x = Core::App()->getWidth() / physRatio;
    rightWall->position.y = (Core::App()->getHeight() / 2) / physRatio;

    me = Make<Polygon>();
    me->setAsBox(25 / physRatio, 50 / physRatio);
    me->useDefinition(cDef);
    me->fixedRotation = true;
    me->position.x = (Core::App()->getWidth() / 4) / physRatio;
    me->position.y = (Core::App()->getHeight() / 2) / physRatio;

    pWorld.addCollider(ground);
    pWorld.addCollider(top);
    pWorld.addCollider(leftWall);
    pWorld.addCollider(rightWall);
    pWorld.addCollider(me);

    timer.initialize(5000, [this, physRatio, cDef](){
      glm::vec2 pos = {math::random(Core::App()->getWidth() / 4, Core::App()->getWidth() / 2 + Core::App()->getWidth() / 4), Core::App()->getHeight() - 200};

      Pointer<Polygon> bo = Make<Polygon>();
      bo->setAsBox(50 / physRatio, 50 / physRatio);
      bo->useDefinition(cDef);
      bo->position.x = pos.x / physRatio;
      bo->position.y = pos.y / physRatio;
      pWorld.addCollider(bo);

      polygons.push_back(bo);
      if (polygons.size() > 40) {
        auto po = polygons.front();
        polygons.pop_front();
        pWorld.removeCollider(po);
      }

      timer.reset();
    });

    auto zone = Make<ZoneAttractor>();
    zone->position.x = (Core::App()->getWidth() / 2) / physRatio;
    zone->position.y = 0;
    zone->width = (Core::App()->getWidth()) / physRatio;
    zone->height = 150 / physRatio;
    zone->velocity = {-10, 60};

    auto leftZone = Make<ZoneAttractor>();
    leftZone->position.x = 0;
    leftZone->position.y = (Core::App()->getHeight() / 2) / physRatio;
    leftZone->width = 150 / physRatio;
    leftZone->height = Core::App()->getHeight() / physRatio;
    leftZone->velocity = {0, 25};
    leftZone->priority = 1;

    auto cornerZone = Make<ZoneAttractor>();
    cornerZone->position.x = 50 / physRatio;
    cornerZone->position.y = 50 / physRatio;
    cornerZone->width = 150 / physRatio;
    cornerZone->height = 150 / physRatio;
    cornerZone->velocity = {-50, -50};
    cornerZone->priority = 10;

    auto topZone = Make<ZoneAttractor>();
    topZone->position.x = (Core::App()->getWidth() / 2 - 100) / physRatio;
    topZone->position.y = Core::App()->getHeight() / physRatio;
    topZone->width = (Core::App()->getWidth() - 100) / physRatio;
    topZone->height = 150 / physRatio;
    topZone->velocity = {50, 0};
    topZone->priority = 2;

    auto point = Make<PointAttractor>();
    point->position.x = (Core::App()->getWidth() / 2) / physRatio;
    point->position.y = (Core::App()->getHeight() / 2) / physRatio;
    point->radius = 150 / physRatio;
    point->velocity = {5.f, 5.f};
    point->priority = 3;

    me->airFrictionScale = 1.f;

//    pWorld.addAttractor(zone);
    pWorld.addAttractor(leftZone);
    pWorld.addAttractor(topZone);
    pWorld.addAttractor(cornerZone);

    pWorld.addAttractor(point);
    pWorld.setWireframeMode(true);
  }

  virtual void onKeyPressed(KeyEvent::Key key) override {}

  virtual void update(float delta) override {
    timer.update(delta);
    pWorld.step(1/60.f);

    float vel = 200;
    if (Core::Events()->isKeyPressed(KeyEvent::Key::Left)) {
      me->velocity.x = math::clamp(me->velocity.x - vel * delta, -50, me->velocity.x);
    }

    else if (Core::Events()->isKeyPressed(KeyEvent::Key::Right)) {
      me->velocity.x = math::clamp(me->velocity.x + vel * delta, me->velocity.x, 50);
    }

    if (Core::Events()->isKeyJustPressed(KeyEvent::Key::Up)) {
      me->velocity.y = math::clamp(me->velocity.y + vel / 10.f, me->velocity.y, 50);
    }

    else if (Core::Events()->isKeyPressed(KeyEvent::Key::Down)) {
      me->velocity.y = math::clamp(me->velocity.y - vel / 10.f, -50, me->velocity.y);
    }
  }

  virtual void render() override {
    Framebuffer::clear(Color(0, 0, 0));

    batch->begin();
    pWorld.render(batch);
    batch->end();
  }

private:
  World pWorld;

  SimpleBatch2D::Ref batch;
  OrthographicCamera::Ref camera;

  CallbackTimer timer;

  std::deque<Pointer<Polygon>> polygons;
  Pointer<Polygon> me;
};
