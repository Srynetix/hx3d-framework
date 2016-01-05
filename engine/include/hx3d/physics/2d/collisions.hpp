#ifndef HX3D_PHYSICS_2D_COLLISIONS
#define HX3D_PHYSICS_2D_COLLISIONS

#include "hx3d/physics/2d/manifold.hpp"

namespace hx3d {
namespace physics2d {

/**
@brief Collision test between two circles.

@param m Manifold
@param a First circle
@param b Second circle

@return True/False
*/
bool checkCollisions(Manifold& m, Ptr<Circle> a, Ptr<Circle> b);

/**
@brief Collision test between polygon and circle.

@param m Manifold
@param a Polygon
@param b Circle

@return True/False
*/
bool checkCollisions(Manifold& m, Ptr<Polygon> a, Ptr<Circle> b);

/**
@brief Collision test between circle and polygon.

@param m Manifold
@param a Circle
@param b Polygon

@return True/False
*/
bool checkCollisions(Manifold& m, Ptr<Circle> a, Ptr<Polygon> b);

/**
@brief Collision test between two polygons.

@param m Manifold
@param a First polygon
@param b Second polygon

@return True/False
*/
bool checkCollisions(Manifold& m, Ptr<Polygon> a, Ptr<Polygon> b);

} /* physics2d */
} /* hx3d */

#endif
