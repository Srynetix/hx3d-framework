#include "hx3d/physics/2d/material.hpp"

namespace hx3d {
namespace physics2d {

Material::Material() {
  staticFriction = 0.5f;
  dynamicFriction = 0.3f;
  restitution = 0.2f;
}

} /* physics2d */
} /* hx3d */
