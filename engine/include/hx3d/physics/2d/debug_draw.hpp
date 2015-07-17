/*
    2D physics debug drawing.
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


    TODO
    > Finish the class.
*/

#ifndef HX3D_PHYSICS_2D_DEBUGDRAW
#define HX3D_PHYSICS_2D_DEBUGDRAW

#include <Box2D/Common/b2Draw.h>

namespace hx3d {
namespace physics2d {

class DebugDraw: public b2Draw {
public:
  /**
  Draw a closed polygon provided in CCW order.
  */
  virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

  /**
  Draw a solid closed polygon provided in CCW order.
  */
  virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

  /**
  Draw a circle.
  */
  virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;

  /**
  Draw a solid circle.
  */
  virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;

  /**
  Draw a line segment.
  */
  virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

  /**
  Draw a transform. Choose your own length scale.
  @param xf a transform.
  */
  virtual void DrawTransform(const b2Transform& xf) override;
};

} /* physics2d */
} /* hx3d */

#endif
