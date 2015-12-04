#include "hx3d/physics/2d/mass.hpp"

namespace hx3d {
namespace physics2d {

Mass::Mass() {
  mass = 0;
  invMass = 0;

  inertia = 0;
  invInertia = 0;
}

void Mass::setMass(float amount) {
  mass = amount;
  invMass = (amount == 0) ? 0 : 1.f / amount;
}

void Mass::setInertia(float amount) {
  inertia = amount;
  invInertia = (amount == 0) ? 0 : 1.f / amount;
}

} /* physics2d */
} /* hx3d */
