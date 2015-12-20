#include "hx3d/physics/2d/attractors/point_attractor.hpp"

#include "hx3d/math/vector_utils.hpp"

namespace hx3d {
namespace physics2d {

PointAttractor::PointAttractor():
  Attractor(Type::Point),
  position(0, 0),
  velocity(0, 0),
  radius(0)
  {}

bool PointAttractor::overlaps(const Ptr<Collider>& collider) {
  if (radius == 0) return false;

  float dx = position.x - collider->position.x;
  float dy = position.y - collider->position.y;
  return dx * dx + dy * dy <= radius * radius;
}

void PointAttractor::computeForce(const Ptr<Collider>& collider, const float dt) {
  glm::vec2 dir = math::normalize(position - collider->position);
  dir *= velocity;
  collider->gravityForce += dir;
}

}
}
