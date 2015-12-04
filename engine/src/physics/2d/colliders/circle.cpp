#include "hx3d/physics/2d/colliders/circle.hpp"

namespace hx3d {
namespace physics2d {
namespace colliders {

Circle::Circle(float radius, const Type colliderType):
    Collider(Shape::Circle, colliderType),
    radius(radius)
{
  setDensity(1.f);
}

void Circle::setOrientation(float angle) {
  orientation = angle;
}

void Circle::computeMass(float density) {
  massData.setMass(density);
}

} /* colliders */
} /* physics2d */
} /* hx3d */
