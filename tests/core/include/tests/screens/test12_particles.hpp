#include "./base_test_screen.hpp"

#include "hx3d/core/events.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

#include <set>
#include <queue>

using namespace hx3d;

template <class T>
class Pool {
public:

  template <class... Args>
  Pool(unsigned int size, Args... args): size(size) {
    for (unsigned int i = 0; i < size; ++i) {
      Ptr<T> p = Make<T>(args...);
      _freed.push(p);
    }
  }

  ~Pool() {}

  Ptr<T> take() {
    if (_freed.size() > 0) {
      Ptr<T> ptr = _freed.front();
      _freed.pop();
      _working.insert(ptr);
      return ptr;
    }

    Log.Error("Pool: no more freed.");
    return nullptr;
  }

  void release(Ptr<T> ptr) {
    if (_working.find(ptr) != _working.end()) {
      _working.erase(ptr);
      ptr.reset();
      _freed.push(ptr);
    }

    else {
      Log.Error("Pool: Ptr is not working.");
    }
  }

  std::set<Ptr<T>> getWorking() {
    return _working;
  }

  unsigned int size;

private:
  std::queue<Ptr<T>> _freed;
  std::set<Ptr<T>> _working;
};

class Particle {
public:
  glm::vec3 position;
  glm::vec3 size;

  float baseLife;
  float life;

  float speed;
  bool dead;
  Sprite sprite;
  Color color;

  Particle() {
    life = baseLife = 1.f;
    dead = false;
    speed = 20.f;
    color = Color::White;
  }

  void setTexture(Ptr<Texture> texture) {
    sprite.setTexture(texture);
  }

  void update(float delta) {
    life -= delta;

    if (life <= 0.f) {
      dead = true;
      return;
    }

    else {
      float normalizedLife = life / baseLife;
      color.a = 255 * normalizedLife;
      sprite.setTint(color);

      position.y -= speed * delta;
    }
  }

  void draw(Batch& batch) {
    sprite.transform.position = position;
    sprite.transform.size = size;

    batch.draw(sprite);
  }
};

class ParticleEmitter {
public:
  ParticleEmitter():
    particles(100)
  {
    texture = Core::Assets()->get<Texture>("box");
  }

  glm::vec3 position;
  glm::vec3 emitter_size;
  glm::vec3 particle_size;

  void emit(unsigned int qty) {
    for (unsigned int i = 0; i < qty; ++i) {
      emitOne();
    }
  }

  void update(float delta) {
    const auto& working = particles.getWorking();

    for (auto i = working.begin(); i != working.end();) {
      const Ptr<Particle>& p = *i;
      if (p->dead) {
        particles.release(p);
      } else {
        p->update(delta);
        ++i;
      }
    }
  }

  void draw(Batch& batch) {
    const auto& working = particles.getWorking();
    for (auto it = working.begin(); it != working.end(); ++it) {
      const Ptr<Particle> &p = *it;
      p->draw(batch);
    }
  }

  void setTexture(Ptr<Texture> texture) {
    this->texture = texture;
  }

private:
  void emitOne() {
    Ptr<Particle> p = particles.take();

    p->setTexture(texture);
    p->position.x = math::random(position.x - emitter_size.x / 2.f, position.x + emitter_size.x / 2.f);
    p->position.y = math::random(position.y - emitter_size.y / 2.f, position.y + emitter_size.y / 2.f);
    p->size.x = particle_size.x;
    p->size.y = particle_size.y;
  }

  Pool<Particle> particles;
  Ptr<Texture> texture;
};

class ParticleManager {
public:
  ParticleManager() {}

  void addEmitter(Ptr<ParticleEmitter> emitter) {
    emitters.push_back(emitter);
  }

  void update(float delta) {
    for (Ptr<ParticleEmitter>& emitter: emitters) {
      emitter->update(delta);
    }
  }

  void draw(Batch& batch) {
    glDisable(GL_DEPTH_TEST);
    for (Ptr<ParticleEmitter>& emitter: emitters) {
      emitter->draw(batch);
    }
    glEnable(GL_DEPTH_TEST);
  }

  std::vector<Ptr<ParticleEmitter>> emitters;
};

class Test12: public BaseTestScreen {
public:
  Test12():
    fps(Core::Assets()->get<Font>("default"))
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    fps.setContent("FPS: ");
    fps.transform.position.x = 10;
    fps.transform.position.y = Core::App()->getHeight() - 20;
    fps.transform.position.z = 0.5f;

/*
    emitter = Make<ParticleEmitter>();
    emitter->position = glm::vec3(Core::App()->getWidth() / 2, Core::App()->getHeight() / 2, 0);
    emitter->emitter_size = glm::vec3(500, 50, 0);
    emitter->particle_size = glm::vec3(100, 100, 0);
    emitter->setTexture(Core::Assets()->get<Texture>("fire"));
    emitter->emit(5);

    particles.addEmitter(emitter);


    timer.initialize(50, [this](){
      emitter->emit(5);
      timer.reset();
    });
*/
  }

  virtual void update(float delta) override {
    camera.update();
    // timer.update();
    // particles.update(delta);

    fps.setContent(format("FPS: %2.2f", 1.f/delta));
  }

  void render() {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();
    // particles.draw(batch);
    batch.draw(fps);
    batch.end();
  }

private:
  Ptr<ParticleEmitter> emitter;
  ParticleManager particles;
  OrthographicCamera camera;
  Sprite sprite;
  CallbackTimer timer;

  gui::Text fps;

  Batch batch;
};
