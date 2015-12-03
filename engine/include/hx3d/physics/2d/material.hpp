#ifndef HX3D_PHYSICS_2D_MATERIAL
#define HX3D_PHYSICS_2D_MATERIAL

namespace hx3d {
namespace physics2d {

struct Material {
  Material() {
    staticFriction = 0.5f;
    dynamicFriction = 0.3f;
    restitution = 0.2f;
  }

  float staticFriction;
  float dynamicFriction;
  float restitution;
};

} /* physics2d */
} /* hx3d */


#endif
