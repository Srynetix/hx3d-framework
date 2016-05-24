/*
    Physics node.
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

#ifndef HX3D_ECS_NODES_PHYSICSNODE
#define HX3D_ECS_NODES_PHYSICSNODE

#include "hx3d/ecs/node.hpp"

#include "hx3d/physics/2d/world.hpp"
#include "hx3d/physics/2d/collider.hpp"

#include "hx3d/graphics/batches/batch.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/texture.hpp"

namespace hx3d {
namespace ecs {

/**
@brief Drawable physics node.
*/
class PhysicsNode: public Node {
public:
  /**
  @brief Create a physics node
  */
  PhysicsNode(std::string name, physics2d::World* world, physics2d::Collider::Type type, float x, float y, float w, float h, std::string category = "", std::string mask = "", const Pointer<graphics::Texture> texture = nullptr);

  virtual void draw(const Pointer<graphics::Batch>& batch) override;
  virtual void update(float delta) override;

protected:
  physics2d::World* _world;
  Pointer<physics2d::Collider> _collider;

  Pointer<graphics::Texture> _texture;
  Pointer<graphics::Sprite> _sprite;
};

} /* ecs */
} /* hx3d */

#endif /* HX3D_ECS_NODES_PHYSICSNODE */
