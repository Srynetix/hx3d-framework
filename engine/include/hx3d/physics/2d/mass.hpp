#ifndef HX3D_PHYSICS_2D_MASS
#define HX3D_PHYSICS_2D_MASS

namespace hx3d {
namespace physics2d {

struct Mass {
  Mass() {
    mass = 0;
    invMass = 0;

    inertia = 0;
    invInertia = 0;
  }

  void setMass(float amount) {
    mass = amount;
    invMass = (amount == 0) ? 0 : 1.f / amount;
  }

  void setInertia(float amount) {
    inertia = amount;
    invInertia = (amount == 0) ? 0 : 1.f / amount;
  }

  //////////////////

  float mass;
  float invMass;

  float inertia;
  float invInertia;
};


} /* physics2d */
} /* hx3d */


#endif
