#ifndef HX3D_PHYSICS_2D_ATTRACTOR
#define HX3D_PHYSICS_2D_ATTRACTOR

#include "hx3d/utils/ptr.hpp"

#include "hx3d/physics/2d/collider.hpp"

namespace hx3d {
namespace physics2d {

struct Attractor {

  enum class Type {
    Global = 1,
    Zone,
    Point
  };

  Type type;
  unsigned int priority;

  Attractor(Type type);

  virtual bool overlaps(const Ptr<Collider>& collider) = 0;
  virtual void computeForce(const Ptr<Collider>& collider, const float dt) = 0;

  static void setCurrentAttractor(const Ptr<Collider>& collider, const Ptr<Attractor>& attractor, const float dt);
  static void applyForce(const Ptr<Collider>& collider, const Ptr<Attractor>& attractor, const float dt);
};

} /* physics2d */
} /* hx3d */

#endif
