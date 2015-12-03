#include "./base_test_screen.hpp"

#include "hx3d/graphics/batch.hpp"
#include "hx3d/physics/2d/world.hpp"

using namespace hx3d;

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

    text.transform.position.x = 100;
    text.transform.position.y = 100;
    text.transform.position.z = 0.9f;

    physics2d::ColliderDefinition cDef;
    cDef.material.restitution = 0.f;
    cDef.material.staticFriction = 0.f;
    cDef.material.dynamicFriction = 0.f;

    ground = Make<physics2d::Polygon>(physics2d::Collider::Type::Static);
    top = Make<physics2d::Polygon>(physics2d::Collider::Type::Static);
    leftWall = Make<physics2d::Polygon>(physics2d::Collider::Type::Static);
    rightWall = Make<physics2d::Polygon>(physics2d::Collider::Type::Static);

    ground->setAsBox(Core::App()->getWidth() / 30.f, 50 / 30.f);
    ground->useDefinition(cDef);
    ground->position.x = (Core::App()->getWidth() / 2) / 30.f;
    ground->position.y = 0;

    top->setAsBox(Core::App()->getWidth() / 30.f, 50 / 30.f);
    top->useDefinition(cDef);
    top->position.x = (Core::App()->getWidth() / 2) / 30.f;
    top->position.y = Core::App()->getHeight() / 30.f;

    leftWall->setAsBox(50 / 30.f, Core::App()->getHeight() / 30.f);
    leftWall->useDefinition(cDef);
    leftWall->position.x = 0;
    leftWall->position.y = (Core::App()->getHeight() / 2) / 30.f;

    rightWall->setAsBox(50 / 30.f, Core::App()->getHeight() / 30.f);
    rightWall->useDefinition(cDef);
    rightWall->position.x = Core::App()->getWidth() / 30.f;
    rightWall->position.y = (Core::App()->getHeight() / 2) / 30.f;

    me = Make<physics2d::Polygon>();
    me->setAsBox(25 / 30.f, 50 / 30.f);
    me->useDefinition(cDef);
    me->position.x = (Core::App()->getWidth() / 2) / 30.f;
    me->position.y = (Core::App()->getHeight() / 2) / 30.f;

    pWorld.addCollider(ground);
    pWorld.addCollider(top);
    pWorld.addCollider(leftWall);
    pWorld.addCollider(rightWall);
    pWorld.addCollider(me);

    timer.initialize(1000, [this, &cDef](){

      glm::vec2 pos = {math::random(Core::App()->getWidth() / 4, Core::App()->getWidth() / 2 + Core::App()->getWidth() / 4), Core::App()->getHeight() - 200};

      Ptr<physics2d::Polygon> box = Make<physics2d::Polygon>();
      box->setAsBox(50 / 30.f, 50 / 30.f);
      box->useDefinition(cDef);
      box->position.x = pos.x / 30.f;
      box->position.y = pos.y / 30.f;
      pWorld.addCollider(box);
      colliders.push_back(box);

      // timer.reset();
    });

    zone = Make<physics2d::ZoneAttractor>();
    zone->position.x = (Core::App()->getWidth() / 2) / 30.f;
    zone->position.y = 0;
    zone->width = Core::App()->getWidth() / 30.f;
    zone->height = 300 / 30.f;
    zone->velocity = {0, 100};
    // zone->velocity = {0, 0};

    leftZone = Make<physics2d::ZoneAttractor>();
    leftZone->position.x = 0;
    leftZone->position.y = (Core::App()->getHeight() / 2) / 30.f;
    leftZone->width = 100 / 30.f;
    leftZone->height = Core::App()->getHeight() / 30.f;
    leftZone->velocity = {0, 20};
    // leftZone->velocity = {-20, 0};
    leftZone->priority = 1;

    topZone = Make<physics2d::ZoneAttractor>();
    topZone->position.x = (Core::App()->getWidth() / 2 - 100) / 30.f;
    topZone->position.y = Core::App()->getHeight() / 30.f;
    topZone->width = (Core::App()->getWidth() - 100) / 30.f;
    topZone->height = 100 / 30.f;
    topZone->velocity = {20, 0};
    // topZone->velocity = {0, 20};
    topZone->priority = 2;

    point = Make<physics2d::PointAttractor>();
    point->position.x = (Core::App()->getWidth() / 2) / 30.f;
    point->position.y = (Core::App()->getHeight() / 2) / 30.f;
    point->radius = 150 / 30.f;
    point->velocity = {10.f, 10.f};
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

  std::vector<Ptr<physics2d::Collider>> colliders;
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
