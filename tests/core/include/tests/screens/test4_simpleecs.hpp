#include "./base_test_screen.hpp"

#include "hx3d/ecs/engine.hpp"
#include "hx3d/ecs/component.hpp"
#include "hx3d/ecs/system.hpp"
#include "hx3d/ecs/entity.hpp"

#include "hx3d/math/number_utils.hpp"

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

  virtual void process(Ptr<ecs::Entity> entity, float delta) override {
    auto rotComp = getEngine()->getComponent<RotationComponent>(entity);
    rotComp->angle = math::mclamp(rotComp->angle + rotComp->speed, 0.f, 360.f);
  }
};

class Test4: public BaseTestScreen {
public:
  Test4():
    text(Core::Assets()->get<Font>("default")),
    rotText(Core::Assets()->get<Font>("default")),
    angle(0.f)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    sprite.setTexture(Core::Assets()->get<Texture>("box"));

    entity = engine.createEntity();
    engine.registerComponentAdded<RotationComponent>([](Ptr<ecs::Component> component, Ptr<ecs::Entity> entity) {
      Log.Info("Rotation component registered for entity %ld", entity->getId());
    });

    engine.createComponent<RotationComponent>(entity, 1.f);
    engine.createSystem<RotationSystem>();

    sprite.transform.size = glm::vec3(64);
    sprite.transform.position = glm::vec3(Core::App()->getWidth() / 2 - 64 / 2, Core::App()->getHeight() / 2 - 64 / 2, 0);
    sprite.setTint(Color::White);

    text.setContent("This cube is rotating thanks to a RotatingComponent and a RotatingSystem.");
    text.transform.position = glm::vec3(Core::App()->getWidth() / 2 - 550 / 2, Core::App()->getHeight() / 4, 0);

    rotText.transform.position = glm::vec3(20, Core::App()->getHeight() - 20, 0);
  }

  virtual void update(float delta) override {
    engine.update(delta);

    auto rotComp = engine.getComponent<RotationComponent>(entity);
    sprite.transform.rotation.z = glm::radians(rotComp->angle);

    rotText.setContent(format("> RotationComponent: {angle: %.2f, speed: %.2f}", rotComp->angle, rotComp->speed));

    camera.update();
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    batch.begin();

    batch.draw(sprite);

    batch.draw(rotText);
    batch.draw(text, math::Function(Core::App()->getElapsedTime() * 2, 0.5f, [](float& x, float& y, float t) {
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
  Ptr<ecs::Entity> entity;

  OrthographicCamera camera;

  ecs::Engine engine;
  gui::Text text;
  gui::Text rotText;

  Batch batch;
  Sprite sprite;

  float angle;
};
