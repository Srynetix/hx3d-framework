#ifndef HX3D_PHYSICS_2D_COLLISIONS
#define HX3D_PHYSICS_2D_COLLISIONS

#include <cfloat>

#include "hx3d/physics/2d/manifold.hpp"

namespace hx3d {
namespace physics2d {

bool checkCollisions(Manifold& m, Ptr<Circle> a, Ptr<Circle> b);
bool checkCollisions(Manifold& m, Ptr<Polygon> a, Ptr<Circle> b);
bool checkCollisions(Manifold& m, Ptr<Circle> a, Ptr<Polygon> b);
bool checkCollisions(Manifold& m, Ptr<Polygon> a, Ptr<Polygon> b);

}
}

#endif
