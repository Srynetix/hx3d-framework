#ifndef HX3D_PHYSICS_2D_MASS
#define HX3D_PHYSICS_2D_MASS

namespace hx3d {
namespace physics2d {

struct Mass {
  Mass();

  void setMass(float amount);
  void setInertia(float amount);

  //////////////////

  float mass;
  float invMass;

  float inertia;
  float invInertia;
};


} /* physics2d */
} /* hx3d */


#endif
