#include "./base_test_screen.hpp"

#include "hx3d/physics/2d/body_def.hpp"
#include "hx3d/physics/2d/shape.hpp"

#include "hx3d/ecs/z_graph.hpp"

#include "hx3d/math/random.hpp"

using namespace hx3d;

class Box: public ecs::ZNode {
public:
  Box(std::string name):
    ecs::ZNode(name)
  {
    sprite.setTexture(Core::Assets()->get<Texture>("box"));
  }

  void create(b2World& world, float x, float y, float w, float h) {
    b2BodyDef def;
    b2PolygonShape shape;
    b2FixtureDef fixture;

    def = physics2d::BodyDef::create(
      b2_dynamicBody,
      glm::vec2(x, y),
      100.f
    );

    shape = physics2d::Shape::buildBox(
      w,
      h,
      100.f
    );

    body = world.CreateBody(&def);
    fixture.shape = &shape;
    body->CreateFixture(&fixture);

    transform.size = glm::vec3(w, h, 0);
  }

  void update() {
    if (body) {
      b2Vec2 bodyPosition = body->GetPosition();
      transform.position.x = bodyPosition.x * 100.f;
      transform.position.y = bodyPosition.y * 100.f;

      sprite.transform = transform;
    }
  }

  void draw(Batch& batch) {
    batch.draw(sprite);
  }

  Sprite sprite;
  b2Body* body;
};

class Test6: public BaseTestScreen {
public:
  Test6():
    groundSprite(Core::Assets()->get<Texture>("box")),
    world(b2Vec2(0, -9.81f)),
    text(Core::Assets()->get<Font>("default")),
    angle(0.f)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    groundSprite.setTint(Color(255, 127, 65));
    groundSprite.transform.size = glm::vec3(Core::App()->getWidth(), 50.f, 0);

    text.transform.position = glm::vec3(20, Core::App()->getHeight() - 100, 0);

    ////////////////////////////

    b2BodyDef groundDef;
    b2PolygonShape shape;
    b2FixtureDef groundFixture;

    groundDef = physics2d::BodyDef::create(
      b2_staticBody,
      glm::vec2(Core::App()->getWidth() / 2, 50.f),
      100.f
    );
    shape = physics2d::Shape::buildBox(
      Core::App()->getWidth(),
      50.f,
      100.f
    );
    groundBody = world.CreateBody(&groundDef);
    groundFixture.shape = &shape;
    groundBody->CreateFixture(&groundFixture);

    /////////////////////////

    for (unsigned int i = 0; i < 10; ++i) {
      Ptr<Box> box = graph.createAtRoot<Box>(format("box%ld", i));
      box->create(world, math::random(0.f, Core::App()->getWidth()), 600.f, 25.f, 25.f);
    }
  }

  void update() {
    camera.update();
    graph.update();

    world.Step(1.f/60.f, 5, 7);

    b2Vec2 groundPos = groundBody->GetPosition();
    groundSprite.transform.position = glm::vec3(groundPos.x * 100.f, groundPos.y * 100.f, 0);

    text.setContent("Entities: 0");
  }

  void render() {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    batch.draw(groundSprite);
    batch.draw(text);

    graph.draw(batch);

    batch.end();

    angle += 0.5f;
    if (angle > 360.f) {
      angle -= 360.f;
    }
  }

private:
  OrthographicCamera camera;

  Batch batch;
  Sprite groundSprite;

  b2World world;
  b2Body* boxBody;
  b2Body* groundBody;

  gui::Text text;

  ecs::ZGraph graph;

  float angle;
};
