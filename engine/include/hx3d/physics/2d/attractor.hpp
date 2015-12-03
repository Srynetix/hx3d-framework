#ifndef HX3D_PHYSICS_2D_ATTRACTOR
#define HX3D_PHYSICS_2D_ATTRACTOR

#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace physics2d {

struct Attractor {

  enum class Type {
    Global = 1,
    Zone,
    Point
  };

  virtual bool overlaps(Ptr<Collider> collider) = 0;
  virtual void computeForce(Ptr<Collider> collider, float dt) = 0;

  static void setCurrentAttractor(Ptr<Collider> collider, Ptr<Attractor> attractor, float dt) {
    collider->attractors.current = attractor;
    attractor->computeForce(collider, dt);
  }

  static void applyForce(Ptr<Collider> collider, Ptr<Attractor> attractor, float dt) {
    if (attractor->overlaps(collider)) {
      Ptr<Attractor> current = collider->attractors.current;
      if (!current) {
        setCurrentAttractor(collider, attractor, dt);
        return;
      }

      if (current == attractor) {
        attractor->computeForce(collider, dt);
        return;
      }

      unsigned int currentType = static_cast<unsigned int>(current->type);
      unsigned int attractorType = static_cast<unsigned int>(attractor->type);

      if (attractorType > currentType) {
        setCurrentAttractor(collider, attractor, dt);
      }

      else if (attractorType == currentType) {
        if (attractor->priority > current->priority) {
          setCurrentAttractor(collider, attractor, dt);
        }
      }

      else {
        if (!current->overlaps(collider)) {
          setCurrentAttractor(collider, attractor, dt);
        }
      }
    }
  }

  Attractor(Type type): type(type), priority(0) {}

  Type type;
  unsigned int priority;
};

struct ZoneAttractorDefinition {

  ZoneAttractorDefinition(): unitCoef(1/30.f) {}

  float unitCoef;

  glm::vec2 position;
  glm::vec2 velocity;
  float width;
  float height;
};

struct ZoneAttractor: public Attractor {
  glm::vec2 position;
  glm::vec2 velocity;
  float width;
  float height;

  ZoneAttractor(): Attractor(Type::Zone) {
    position = {0, 0};
    velocity = {0, 0};
    width = 0;
    height = 0;
  }

  ZoneAttractor(ZoneAttractorDefinition& def): ZoneAttractor() {
    useDefinition(def);
  }

  void useDefinition(ZoneAttractorDefinition& def) {
    position = def.position * def.unitCoef;
    width = def.width * def.unitCoef;
    height = def.height * def.unitCoef;

    velocity = def.velocity;
  }

  virtual bool overlaps(Ptr<Collider> collider) override {
    bool x_overlap = (collider->position.x >= position.x - width / 2 && collider->position.x <= position.x + width / 2);
    if (x_overlap) {
      bool y_overlap = (collider->position.y >= position.y - height / 2 && collider->position.y <= position.y + height / 2);
      if (y_overlap) {
        return true;
      }
    }

    return false;
  }

  virtual void computeForce(Ptr<Collider> collider, float dt) override {
    collider->gravityForce += velocity * (dt / 2);
  }
};

struct PointAttractor: public Attractor {
  float radius;
  glm::vec2 position;
  glm::vec2 velocity;

  PointAttractor(): Attractor(Type::Point) {
    position = {0, 0};
    velocity = {0, 0};
    radius = 100.f;
  }

  virtual bool overlaps(Ptr<Collider> collider) override {
    if (radius == 0) return false;

    float dx = position.x - collider->position.x;
    float dy = position.y - collider->position.y;
    return dx * dx + dy * dy <= radius * radius;
  }

  virtual void computeForce(Ptr<Collider> collider, float dt) override {
    glm::vec2 dir = math::normalize(position - collider->position);
    dir *= velocity;
    collider->gravityForce += dir * (dt / 2);
  }
};

struct GlobalAttractor: public Attractor {
  glm::vec2 velocity;

  GlobalAttractor(glm::vec2 v):
    Attractor(Type::Global), velocity(v)
    {}

  virtual bool overlaps(Ptr<Collider> collider) override {
    return true;
  }

  virtual void computeForce(Ptr<Collider> collider, float dt) override {
    collider->gravityForce += velocity * (dt / 2);
  }
};

} /* physics2d */
} /* hx3d */

#endif
