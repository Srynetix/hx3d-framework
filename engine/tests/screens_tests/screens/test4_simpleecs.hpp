#include "../test_screen.hpp"

#include "hx3d/ecs/engine.hpp"
#include "hx3d/ecs/component.hpp"
#include "hx3d/ecs/system.hpp"
#include "hx3d/ecs/entity.hpp"

#include "hx3d/graphics/font.hpp"
#include "hx3d/gui/text.hpp"

using namespace hx3d;

class RotationComponent: public ecs::Component {
public:
  RotationComponent(float speed): angle(0.f), speed(speed) {}

  float angle;
  float speed;
};

class RotationSystem: public ecs::System {
public:
  RotationSystem() {
    setRequiredFamily<RotationComponent>();
  }

  virtual void process(Ptr<ecs::Entity> entity) override {
    auto rotComp = getEngine()->getComponent<RotationComponent>(entity);
    rotComp->angle += rotComp->speed;

    if (rotComp->angle > 360.f) {
      rotComp->angle -= 360.f;
    }
  }
};

class Test4: public TestScreen {
public:
  Test4():
    camera(Make<OrthographicCamera>()),
    text(Core::Assets()->get<Font>("default")),
    rotText(Core::Assets()->get<Font>("default")),
    sprite(Core::Assets()->get<Texture>("box")),
    angle(0.f)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    entity = engine.createEntity();
    engine.registerComponentAdded<RotationComponent>([](Ptr<ecs::Component> component, Ptr<ecs::Entity> entity) {
      Log.Info("Rotation component registered for entity %ld", entity->getId());
    });

    engine.createComponent<RotationComponent>(entity, 1.f);
    engine.createSystem<RotationSystem>();

    sprite.transform.size = glm::vec3(64);
    sprite.transform.position = glm::vec3(Core::App()->getWidth() / 2 - 64 / 2, Core::App()->getHeight() / 2 - 64 / 2, 0);
    sprite.setTint(Color(255, 255, 255));

    text.setContent("This cube is rotating thanks to a RotatingComponent and a RotatingSystem.");
    text.transform.position = glm::vec3(Core::App()->getWidth() / 2 - 550 / 2, Core::App()->getHeight() / 4, 0);

    rotText.transform.position = glm::vec3(20, Core::App()->getHeight() - 20, 0);
  }

  void update() {
    engine.update();

    auto rotComp = engine.getComponent<RotationComponent>(entity);
    sprite.transform.rotation.z = glm::radians(rotComp->angle);

    rotText.setContent(format("> RotationComponent: {angle: %.2f, speed: %.2f}", rotComp->angle, rotComp->speed));

    camera->update();
  }

  void render() {
    Camera::clear(Color(0, 0, 0));

    batch.begin();

    batch.draw(sprite);

    batch.draw(rotText);
    batch.draw(text, math::Function(Core::App()->getElapsedTime() / 20.f, 0.5f, [](float& x, float& y, float t) {
      x = std::abs(std::sin(t / 2.f));
      y = std::sin(t) * 2.5f;
    }));

    batch.end();

    angle += 0.5f;
    if (angle > 360.f) {
      angle -= 360.f;
    }
  }

private:
  Ptr<OrthographicCamera> camera;
  Ptr<ecs::Entity> entity;

  ecs::Engine engine;
  gui::Text text;
  gui::Text rotText;

  Batch batch;
  Sprite sprite;

  float angle;
};
