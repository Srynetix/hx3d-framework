#include "hx3d/physics/2d/attractors/global_attractor.hpp"

namespace hx3d {
namespace physics2d {

GlobalAttractor::GlobalAttractor(glm::vec2 velocity):
  Attractor(Type::Global),
  velocity(velocity)
  {}


bool GlobalAttractor::overlaps(const Pointer<Collider>& collider) {
  return true;
}

void GlobalAttractor::computeForce(const Pointer<Collider>& collider, const float dt) {
  collider->gravityForce += velocity;
}

}
}
