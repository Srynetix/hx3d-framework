#include "hx3d/physics/2d/manifold.hpp"

#include "hx3d/physics/2d/collisions.hpp"
#include "hx3d/physics/2d/collider.hpp"

#include "hx3d/physics/2d/colliders/polygon.hpp"
#include "hx3d/physics/2d/colliders/circle.hpp"

#include "hx3d/math/vector_utils.hpp"

#include <glm/glm.hpp>

namespace hx3d {
namespace physics2d {

Manifold::Manifold(const Pointer<Collider>& a, const Pointer<Collider>& b): a(a), b(b) {
  penetration = 0.f;
  normal = {0, 0};
  mixedRestitution = 0.f;
  mixedDynamicFriction = 0.f;
  mixedStaticFriction = 0.f;
  disabled = false;
}

bool Manifold::solve() {
  bool value = false;

  if (a->shape == Collider::Shape::Circle && b->shape == Collider::Shape::Circle)
    value = checkCollisions(*this, std::dynamic_pointer_cast<Circle>(a), std::dynamic_pointer_cast<Circle>(b));
  else if (a->shape == Collider::Shape::Circle && b->shape == Collider::Shape::Polygon)
    value = checkCollisions(*this, std::dynamic_pointer_cast<Circle>(a), std::dynamic_pointer_cast<Polygon>(b));
  else if (a->shape == Collider::Shape::Polygon && b->shape == Collider::Shape::Circle)
    value = checkCollisions(*this, std::dynamic_pointer_cast<Polygon>(a), std::dynamic_pointer_cast<Circle>(b));
  else if (a->shape == Collider::Shape::Polygon && b->shape == Collider::Shape::Polygon)
    value = checkCollisions(*this, std::dynamic_pointer_cast<Polygon>(a), std::dynamic_pointer_cast<Polygon>(b));

  return value;
}

void Manifold::initialize() {
  if (disabled) return;

  mixedRestitution = (a->material.restitution + b->material.restitution) / 2;
  mixedStaticFriction = std::sqrt(a->material.staticFriction * b->material.staticFriction);
  mixedDynamicFriction = std::sqrt(a->material.dynamicFriction * b->material.dynamicFriction);

  for (unsigned int i = 0; i < contacts.size(); ++i) {
    glm::vec2 ra = contacts[i] - a->position;
    glm::vec2 rb = contacts[i] - b->position;

    glm::vec2 rv = b->velocity + math::cross(b->angularVelocity, rb) - a->velocity - math::cross(a->angularVelocity, ra);

    if (math::squareLength(rv) < (0.025 + math::kEpsilon)) {
      mixedRestitution = 0;
    }
  }
}

void Manifold::applyImpulse() {
  if (disabled) return;

  if (math::epsEqual(a->massData.invMass + b->massData.invMass, 0.f)) {
    infiniteMassCorrection();
    return;
  }

  for (unsigned int i = 0; i < contacts.size(); ++i) {
    glm::vec2 ra = contacts[i] - a->position;
    glm::vec2 rb = contacts[i] - b->position;

    glm::vec2 rv = b->velocity + math::cross(b->angularVelocity, rb) - a->velocity - math::cross(a->angularVelocity, ra);

    float contactVelocity = glm::dot(rv, normal);
    if (contactVelocity > 0)
      return;

    float raCross = math::cross(ra, normal);
    float rbCross = math::cross(rb, normal);

    float invMassSum = a->massData.invMass + b->massData.invMass + (raCross * raCross) * a->massData.invInertia + (rbCross * rbCross) * b->massData.invInertia;

    float j = -(1.f + mixedRestitution) * contactVelocity;
    j /= invMassSum;
    j /= (float)contacts.size();

    glm::vec2 impulse = normal * j;
    a->applyImpulse(-impulse, ra);
    b->applyImpulse(impulse, rb);

    rv = b->velocity + math::cross(b->angularVelocity, rb) - a->velocity - math::cross(a->angularVelocity, ra);

    glm::vec2 nRv = rv - (normal * glm::dot(rv, normal));
    glm::vec2 t = math::normalize(nRv);

    float jt = -glm::dot(rv, t);
    jt /= invMassSum;
    jt /= (float)contacts.size();

    if (math::epsEqual(jt, 0.f))
      return;

    glm::vec2 tangentImpulse;
    if (std::abs(jt) < j * mixedStaticFriction)
      tangentImpulse = t * jt;
    else
      tangentImpulse = t * -j * mixedDynamicFriction;

    a->applyImpulse(-tangentImpulse, ra);
    b->applyImpulse(tangentImpulse, rb);
  }
}

void Manifold::positionalCorrection() {
  if (disabled) return;

  const float kSlop = 0.05f;
  const float percent = 0.4f;

  glm::vec2 correction = (std::max(penetration - kSlop, 0.f) / (a->massData.invMass + b->massData.invMass)) * normal * percent;

  a->position -= correction * a->massData.invMass;
  b->position += correction * b->massData.invMass;
}

void Manifold::infiniteMassCorrection() {
  if (disabled) return;

  a->velocity = {0, 0};
  b->velocity = {0, 0};
}

bool operator<(const Manifold& m1, const Manifold& m2) {
  return m1.penetration < m2.penetration;
}

} /* physics2d */
} /* hx3d */
