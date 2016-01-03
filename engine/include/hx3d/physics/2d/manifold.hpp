#ifndef HX3D_PHYSICS_2D_MANIFOLD
#define HX3D_PHYSICS_2D_MANIFOLD

#include "hx3d/physics/2d/colliders/polygon.hpp"
#include "hx3d/physics/2d/colliders/circle.hpp"

namespace hx3d {
namespace physics2d {

using namespace colliders;

class Manifold {
public:
  Ptr<Collider> a;
  Ptr<Collider> b;

  float penetration;
  bool disabled;
  glm::vec2 normal;
  std::vector<glm::vec2> contacts;

  float mixedRestitution; // e
  float mixedDynamicFriction; // df
  float mixedStaticFriction; // sf

  ///////////

  Manifold(const Ptr<Collider>& a, const Ptr<Collider>& b);

  bool solve();
  void initialize();
  void applyImpulse();

  void positionalCorrection();
  void infiniteMassCorrection();

  friend bool operator<(const Manifold& m1, const Manifold& m2);
};

bool operator<(const Manifold& m1, const Manifold& m2);

}
}

#endif
