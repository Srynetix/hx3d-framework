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

#include "hx3d/ecs/nodes/physics_node.hpp"

namespace hx3d {
namespace ecs {

PhysicsNode::PhysicsNode(std::string name, physics2d::World* world, physics2d::Collider::Type type, float x, float y, float w, float h, std::string category, std::string mask, const Ptr<graphics::Texture> texture):
  Node(name), _world(world), _texture(texture)
{
  _sprite = Make<graphics::Sprite>();

  if (_texture) {
    _sprite->setTexture(_texture);
    _sprite->transform.size.x = w;
    _sprite->transform.size.y = h;
    _sprite->transform.position.x = x;
    _sprite->transform.position.y = y;
  }

  auto& matrix = _world->getCollisionMatrix();

  auto poly = Make<physics2d::colliders::Polygon>(type);
  poly->setAsBox(
    w / _world->getPhysRatio(),
    h / _world->getPhysRatio()
  );

  _collider = poly;
  _collider->category = category == "" ? 0 : matrix.getCategory(category);
  _collider->mask = mask == "" ? 0 : matrix.getMask(mask);

  _world->addCollider(_collider);
}

void PhysicsNode::update(float delta) {
  if (_texture) {
    _sprite->transform.position.x = _collider->position.x * _world->getPhysRatio();
    _sprite->transform.position.y = _collider->position.y * _world->getPhysRatio();
    _sprite->transform.rotation.z = _collider->orientation;
  }
}

void PhysicsNode::draw(const Ptr<graphics::BaseBatch>& batch) {
  if (_texture) {
    batch->draw(_sprite);
  }
}

} /* ecs */
} /* hx3d */
