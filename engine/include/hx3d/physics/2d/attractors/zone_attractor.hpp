#ifndef HX3D_PHYSICS_2D_ATTRACTORS_ZONE_ATTRACTOR
#define HX3D_PHYSICS_2D_ATTRACTORS_ZONE_ATTRACTOR

#include "hx3d/physics/2d/attractor.hpp"

namespace hx3d {
namespace physics2d {

struct ZoneAttractor: public Attractor {

  struct Definition {
    Definition();

    float unitCoef;

    glm::vec2 position;
    glm::vec2 velocity;
    float width;
    float height;
  };

  glm::vec2 position;
  glm::vec2 velocity;
  float width;
  float height;

  ZoneAttractor();
  explicit ZoneAttractor(const Definition& def);

  void useDefinition(const Definition& def);

  virtual bool overlaps(const Ptr<Collider>& collider) override;
  virtual void computeForce(const Ptr<Collider>& collider, const float dt) override;
};

}
}

#endif
