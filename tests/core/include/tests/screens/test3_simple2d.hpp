#include "./base_test_screen.hpp"

using namespace hx3d;

class Test3: public BaseTestScreen {
public:
  Test3():
    text(Core::Assets()->get<Font>("default")),
    angle(0.f)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    sprite.setTexture(Core::Assets()->get<Texture>("box"));

    text.transform.position.x = 100;
    text.transform.position.y = 100;
    text.transform.position.z = 0.9f;
  }

  virtual void update(float delta) override {
    if (Core::Events()->isKeyPressed(KeyEvent::Key::Z)) {
      camera.translate(glm::vec3(0, 2.f, 0));
    }
    else if (Core::Events()->isKeyPressed(KeyEvent::Key::S)) {
      camera.translate(glm::vec3(0, -2.f, 0));
    }
    else if (Core::Events()->isKeyPressed(KeyEvent::Key::Q)) {
      camera.translate(glm::vec3(-2.f, 0, 0));
    }
    else if (Core::Events()->isKeyPressed(KeyEvent::Key::D)) {
      camera.translate(glm::vec3(2.f, 0, 0));
    }

    camera.update();
    text.setContent(format("FPS: %2.2f", 1.f/delta));
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    batch.begin();

    sprite.setTint(Color::White);
    sprite.transform.position.z = -0.5f;

    float boxCount = 50.f;
    float aspectRatio = (float)Core::App()->getWidth() / Core::App()->getHeight();
    float boxSize = (float)Core::App()->getWidth() / boxCount;
    sprite.transform.size = std::abs(std::cos(glm::radians(angle / 2))) * glm::vec3(boxSize);

    for (int j = 0; j < boxCount / aspectRatio; ++j) {
      sprite.transform.position.y = (j * boxSize) + boxSize / 2;

      for (int i = 0; i < boxCount; ++i) {
        sprite.transform.position.x = (i * boxSize) + boxSize / 2;
        sprite.transform.rotation.z = glm::radians(angle * 4);
        batch.draw(sprite);
      }
    }

    sprite.setTint(Color::Green);
    sprite.transform.size = glm::vec3(64);
    sprite.transform.rotation.z = glm::radians(angle * 2);

    sprite.transform.position.x = 100.f;
    sprite.transform.position.y = 100.f;
    sprite.transform.position.z = 0.f;
    batch.draw(sprite);

    sprite.transform.position.x = 125.f;
    sprite.transform.position.y = 125.f;
    sprite.transform.position.z = 0.1f;
    batch.draw(sprite);

    sprite.transform.position.x = 150.f;
    sprite.transform.position.y = 150.f;
    sprite.transform.position.z = 0.f;
    batch.draw(sprite);

    batch.draw(text);

    batch.end();

    angle += 0.5f;
    if (angle > 360.f) {
      angle -= 360.f;
    }
  }

private:
  hx3d::OrthographicCamera camera;
  gui::Text text;

  hx3d::Batch batch;
  hx3d::Sprite sprite;

  float angle;
};
