/*
    2D physics world.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#ifndef HX3D_PHYSICS_2D_WORLD
#define HX3D_PHYSICS_2D_WORLD

#include "hx3d/utils/ptr.hpp"

#include "hx3d/physics/2d/body.hpp"
#include "hx3d/physics/2d/body_def.hpp"
#include "hx3d/physics/2d/debug_draw.hpp"

namespace hx3d {
namespace physics2d {

class World {

public:
  /**
  Create a physical world with a gravity.

  @param gravityX X gravity
  @param gravityY Y gravity
  */
  World(float gravityX, float gravityY);

  /**
  Create a physical body.
  @param def Body definition
  */
  Ptr<Body> createBody(BodyDef def);

  /**
  Enable the debug drawing.
  */
  void enableDebugDraw();
  /**
  Disable the debug drawing.
  */
  void disableDebugDraw();

private:
  Ptr<b2World> _world;
  DebugDraw _debugDraw;
};

} /* physics2d */
} /* hx3d */

#endif
