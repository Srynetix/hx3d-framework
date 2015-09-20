#include "./base_test_screen.hpp"

#include "hx3d/core/events.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

#include "hx3d/graphics/particles/particle_manager.hpp"

using namespace hx3d;

class Test12: public BaseTestScreen {
public:
  Test12()
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    fps.setFont(Core::Assets()->get<Font>("default"));
    fps.setContent("FPS: ");
    fps.transform.position.x = 10;
    fps.transform.position.y = Core::App()->getHeight() - 20;
    fps.transform.position.z = 0.5f;

    particleCount.setFont(Core::Assets()->get<Font>("default"));
    particleCount.setContent("Particles: ");
    particleCount.transform.position.x = 10;
    particleCount.transform.position.y = Core::App()->getHeight() - 40;
    particleCount.transform.position.z = 0.5f;

    emitter = Make<ParticleEmitter>(500);
    emitter->setTexture(Core::Assets()->get<Texture>("fire"));
    emitter->position = glm::vec3(Core::App()->getWidth() / 2, Core::App()->getHeight() / 2, 0);
    emitter->emitter_size = glm::vec3(500, 25, 0);
    emitter->particle_size = glm::vec3(75, 75, 0);
    emitter->gravity = glm::vec3(0, -100.f, 0);
    emitter->velocity = glm::vec3(-50, -200.f, 0);
    emitter->life = 5.f;

    particles.addEmitter(emitter);

    timer.initialize(50, [this](){
      emitter->emit(2);
      timer.reset();
    });
  }

  virtual void update(float delta) override {
    camera.update();
    timer.update(delta);
    particles.update(delta);

    fps.setContent(format("FPS: %2.2f", 1.f/delta));
    particleCount.setContent(format("Particles: %ld", emitter->getParticleCount()));
  }

  void render() {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    particles.draw(batch);
    batch.draw(fps);
    batch.draw(particleCount);

    batch.end();
  }

private:
  Ptr<ParticleEmitter> emitter;
  ParticleManager particles;
  OrthographicCamera camera;
  Sprite sprite;
  CallbackTimer timer;

  gui::Text fps;
  gui::Text particleCount;

  Batch batch;
};
