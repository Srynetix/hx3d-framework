#include "hx3d/physics/2d/attractors/zone_attractor.hpp"

namespace hx3d {
namespace physics2d {

ZoneAttractor::Definition::Definition():
  unitCoef(1/30.f)
  {}

ZoneAttractor::ZoneAttractor():
  Attractor(Type::Zone),
  position(0, 0),
  velocity(0, 0),
  width(0),
  height(0)
  {}

ZoneAttractor::ZoneAttractor(const Definition& def):
  ZoneAttractor()
  {
    useDefinition(def);
  }

void ZoneAttractor::useDefinition(const Definition& def) {
  position = def.position * def.unitCoef;
  width = def.width * def.unitCoef;
  height = def.height * def.unitCoef;

  velocity = def.velocity;
}

bool ZoneAttractor::overlaps(const Pointer<Collider>& collider) {
  bool x_overlap = (collider->position.x >= position.x - width / 2 && collider->position.x <= position.x + width / 2);
  if (x_overlap) {
    bool y_overlap = (collider->position.y >= position.y - height / 2 && collider->position.y <= position.y + height / 2);
    if (y_overlap) {
      return true;
    }
  }

  return false;
}

void ZoneAttractor::computeForce(const Pointer<Collider>& collider, const float dt) {
  collider->gravityForce += velocity;
}

} /* physics2d */
}
