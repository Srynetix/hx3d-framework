#include "hx3d/physics/2d/colliders/circle.hpp"

#include <glm/gtc/constants.hpp>

namespace hx3d {
namespace physics2d {

Circle::Circle(float radius, const Type colliderType):
    Collider(Shape::Circle, colliderType),
    radius(radius)
{
  setDensity(1.f);
}

void Circle::setOrientation(float angle) {
}

void Circle::computeMass(float density) {
  float mass = glm::pi<float>() * radius * radius * density;
  massData.setMass(mass);

  float inertia = mass * radius * radius;
  massData.setInertia(inertia);
}

} /* physics2d */
} /* hx3d */
