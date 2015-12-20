#include "./base_test_screen.hpp"

#include "hx3d/graphics/batch.hpp"
#include "hx3d/physics/2d/world.hpp"

using namespace hx3d;
using namespace hx3d::physics2d;

/*
PROBLEM: TANGENT IMPULSE
*/

class Test13: public BaseTestScreen {
public:
  Test13():
    text(Core::Assets()->get<Font>("default")),
    pWorld({0, -10}, 10)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    float physRatio = pWorld.getPhysRatio();

    text.transform.position.x = 100;
    text.transform.position.y = 100;
    text.transform.position.z = 0.9f;

    Collider::Definition cDef;
    cDef.material.restitution = 0.9f;
    cDef.material.staticFriction = 0.f;
    cDef.material.dynamicFriction = 0.f;

    ground = Make<Polygon>(Collider::Type::Static);
    top = Make<Polygon>(Collider::Type::Static);
    leftWall = Make<Polygon>(Collider::Type::Static);
    rightWall = Make<Polygon>(Collider::Type::Static);

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

    me = Make<physics2d::Polygon>();
    me->setAsBox(25 / physRatio, 50 / physRatio);
    me->useDefinition(cDef);
    me->position.x = (Core::App()->getWidth() / 4) / physRatio;
    me->position.y = (Core::App()->getHeight() / 2) / physRatio;

    pWorld.addCollider(ground);
    pWorld.addCollider(top);
    pWorld.addCollider(leftWall);
    pWorld.addCollider(rightWall);
    pWorld.addCollider(me);

    timer.initialize(500, [this, physRatio, cDef](){
      glm::vec2 pos = {math::random(Core::App()->getWidth() / 4, Core::App()->getWidth() / 2 + Core::App()->getWidth() / 4), Core::App()->getHeight() - 200};
      Log.Info("Pos: %f %f / ph: ", pos.x, pos.y);

      Ptr<physics2d::Polygon> bo = Make<physics2d::Polygon>();
      bo->setAsBox(50 / physRatio, 50 / physRatio);
      bo->useDefinition(cDef);
      bo->position.x = pos.x / physRatio;
      bo->position.y = pos.y / physRatio;
      pWorld.addCollider(bo);
      // colliders.push_back(box);

      timer.reset();
    });

    zone = Make<physics2d::ZoneAttractor>();
    zone->position.x = (Core::App()->getWidth() / 2) / physRatio;
    zone->position.y = 0;
    zone->width = (Core::App()->getWidth()) / physRatio;
    zone->height = 150 / physRatio;
    zone->velocity = {-10, 60};
    // zone->velocity = {0, 0};

    leftZone = Make<physics2d::ZoneAttractor>();
    leftZone->position.x = 0;
    leftZone->position.y = (Core::App()->getHeight() / 2) / physRatio;
    leftZone->width = 150 / physRatio;
    leftZone->height = Core::App()->getHeight() / physRatio;
    leftZone->velocity = {0, 5};
    // leftZone->velocity = {-20, 0};
    leftZone->priority = 1;

    topZone = Make<physics2d::ZoneAttractor>();
    topZone->position.x = (Core::App()->getWidth() / 2 - 100) / physRatio;
    topZone->position.y = Core::App()->getHeight() / physRatio;
    topZone->width = (Core::App()->getWidth() - 100) / physRatio;
    topZone->height = 150 / physRatio;
    topZone->velocity = {10, 0};
    // topZone->velocity = {0, 20};
    topZone->priority = 2;

    point = Make<physics2d::PointAttractor>();
    point->position.x = (Core::App()->getWidth() / 2) / physRatio;
    point->position.y = (Core::App()->getHeight() / 2) / physRatio;
    point->radius = 150 / physRatio;
    point->velocity = {5.f, 5.f};
    point->priority = 3;

    pWorld.addAttractor(zone);
    pWorld.addAttractor(leftZone);
    pWorld.addAttractor(topZone);
    pWorld.addAttractor(point);
  }

  virtual void onKeyPressed(KeyEvent::Key key) override {
    if (key == KeyEvent::Key::Q) {
      me->velocity.x -= 5;
    }

    else if (key == KeyEvent::Key::D) {
      me->velocity.x += 5;
    }

    else if (key == KeyEvent::Key::Z) {
      me->velocity.y += 5;
    }

    else if (key == KeyEvent::Key::S) {
      me->velocity.y -= 5;
    }
  }

  virtual void update(float delta) override {
    text.setContent(format("FPS: %2.2f", 1.f/delta));
    timer.update(delta);
    pWorld.step();
  }

  virtual void render() override {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    pWorld.render(batch);

    batch.draw(text);
    batch.end();
  }

private:
  OrthographicCamera camera;
  gui::Text text;
  physics2d::World pWorld;
  CallbackTimer timer;

  Batch batch;

  Ptr<physics2d::ZoneAttractor> zone;
  Ptr<physics2d::ZoneAttractor> leftZone;
  Ptr<physics2d::ZoneAttractor> topZone;
  Ptr<physics2d::PointAttractor> point;
  Ptr<physics2d::Polygon> ground;
  Ptr<physics2d::Polygon> top;
  Ptr<physics2d::Polygon> leftWall;
  Ptr<physics2d::Polygon> rightWall;

  Ptr<physics2d::Polygon> me;
};
