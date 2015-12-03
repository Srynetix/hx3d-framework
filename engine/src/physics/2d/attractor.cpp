#include "hx3d/physics/2d/attractor.hpp"

namespace hx3d {
namespace physics2d {

Attractor::Attractor(Type type):
  type(type),
  priority(0)
  {}

/////

void Attractor::setCurrentAttractor(const Ptr<Collider>& collider, const Ptr<Attractor>& attractor, const float dt) {
  collider->currentAttractor = attractor;
  attractor->computeForce(collider, dt);
}

void Attractor::applyForce(const Ptr<Collider>& collider, const Ptr<Attractor>& attractor, const float dt) {
  if (attractor->overlaps(collider)) {
    const Ptr<Attractor>& current = collider->currentAttractor;
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

} /* physics2d */
} /* hx3d */
