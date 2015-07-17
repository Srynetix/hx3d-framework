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
*/

#include "hx3d/physics/2d/debug_draw.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace physics2d {

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
  Log.Info("Poly");
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
  Log.Info("SolidPoly");
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
  Log.Info("Circle");
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
  Log.Info("SolidCircle");
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
  Log.Info("Segment");
}

void DebugDraw::DrawTransform(const b2Transform& xf) {
  Log.Info("Transform");
}

} /* physics2d */
} /* hx3d */
