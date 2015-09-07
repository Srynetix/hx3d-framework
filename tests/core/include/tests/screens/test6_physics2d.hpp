#include "./base_test_screen.hpp"

#include "hx3d/physics/2d/body_def.hpp"
#include "hx3d/physics/2d/shape.hpp"

#include "hx3d/ecs/z_graph.hpp"

#include "hx3d/math/random.hpp"
#include "hx3d/math/vector_utils.hpp"

#include "hx3d/utils/timer.hpp"

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

    def = physics2d::BodyDef::create(b2_dynamicBody, glm::vec2(x, y), 100.f);
    shape = physics2d::Shape::buildBox(w, h, 100.f);

    body = world.CreateBody(&def);
    fixture.shape = &shape;
    fixture.density = 1.f;
    body->CreateFixture(&fixture);

    transform.size = glm::vec3(w, h, 0);
    transform.position = glm::vec3(0, 0, -10);

    sprite.transform = transform;

    this->world = &world;
  }

  void update() {
    if (body) {
      b2Vec2 bodyPosition = body->GetPosition();
      float bodyAngle = body->GetAngle();

      glm::vec2 pixelPosition = math::convert(bodyPosition) * 100.f;

      transform.position.x = pixelPosition.x;
      transform.position.y = pixelPosition.y;
      transform.position.z = 0;
      transform.rotation.z = bodyAngle;

      if ((pixelPosition.x < 0 || pixelPosition.x > Core::App()->getWidth()) || (pixelPosition.y < 0 || pixelPosition.y > Core::App()->getHeight())) {
        world->DestroyBody(body);

        destroy();
      }

      sprite.transform = transform;
    }
  }

  void draw(Batch& batch) {
    batch.draw(sprite);
  }

  Sprite sprite;

  b2Body* body;
  b2World* world;
};

class Test6: public BaseTestScreen {
public:
  Test6():
    groundSprite(Core::Assets()->get<Texture>("box")),
    world(b2Vec2(0, -9.81f)),
    text(Core::Assets()->get<Font>("default")),
    timer(50),
    angle(0.f)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    groundSprite.setTint(Color(255, 127, 65));
    groundSprite.transform.size = glm::vec3(Core::App()->getWidth(), 100.f, 0);
    groundSprite.scaleTexture();

    text.transform.position = glm::vec3(20, Core::App()->getHeight() - 100, 0.5);

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
      100.f,
      100.f
    );
    groundBody = world.CreateBody(&groundDef);
    groundFixture.shape = &shape;
    groundBody->CreateFixture(&groundFixture);
  }

  void update() {
    camera.update();
    graph.update();

    world.Step(1.f/60.f, 5, 7);

    b2Vec2 groundPos = groundBody->GetPosition();
    groundSprite.transform.position = glm::vec3(groundPos.x * 100.f, groundPos.y * 100.f, 0);

    unsigned int entities = graph.getNodeCount();
    text.setContent(format("Entities: %d", entities));

    if (timer.isEnded()) {
      static unsigned int count = 0;
      Ptr<Box> box = graph.createAtRoot<Box>(format("box%d", count++));
      box->create(world, math::random(0.f, Core::App()->getWidth()), 600.f, 50.f, 50.f);

      if (entities < 500) {
        timer.reset();
      }
    }
  }

  void render() {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    batch.draw(groundSprite);
    graph.draw(batch);

    batch.draw(text);

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
  Timer timer;

  float angle;
};
