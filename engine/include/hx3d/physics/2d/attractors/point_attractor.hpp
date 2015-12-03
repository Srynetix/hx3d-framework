#ifndef HX3D_PHYSICS_2D_ATTRACTORS_POINT_ATTRACTOR
#define HX3D_PHYSICS_2D_ATTRACTORS_POINT_ATTRACTOR

#include "hx3d/physics/2d/attractor.hpp"

namespace hx3d {
namespace physics2d {

struct PointAttractor: public Attractor {
  glm::vec2 position;
  glm::vec2 velocity;
  float radius;

  PointAttractor();

  virtual bool overlaps(const Ptr<Collider>& collider) override;
  virtual void computeForce(const Ptr<Collider>& collider, const float dt) override;
};

}
}

#endif
