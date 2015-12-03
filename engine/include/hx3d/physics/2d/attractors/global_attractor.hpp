#ifndef HX3D_PHYSICS_2D_ATTRACTORS_GLOBAL_ATTRACTOR
#define HX3D_PHYSICS_2D_ATTRACTORS_GLOBAL_ATTRACTOR

#include "hx3d/physics/2d/attractor.hpp"

namespace hx3d {
namespace physics2d {

struct GlobalAttractor: public Attractor {
  glm::vec2 velocity;

  GlobalAttractor(glm::vec2 velocity);

  virtual bool overlaps(const Ptr<Collider>& collider) override;
  virtual void computeForce(const Ptr<Collider>& collider, const float dt) override;
};

}
}

#endif
