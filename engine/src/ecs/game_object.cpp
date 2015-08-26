/*
    Entity Component System: Game Object.
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

#include "hx3d/ecs/game_object.hpp"

namespace hx3d {

GameObject::GameObject(std::string name):
  GameObject(name, nullptr)
{}

GameObject::GameObject(std::string name, unsigned int id):
  GameObject(name, nullptr, id)
{}

GameObject::GameObject(std::string name, Ptr<GameObject> parent):
  GameObject(name, parent, 0)
{}

GameObject::GameObject(std::string name, Ptr<GameObject> parent, unsigned int id):
  _parent(parent), _id(id), _name(name)
{}

GameObject::~GameObject()
{}

void GameObject::setParent(Ptr<GameObject> parent) {
  _parent = parent;
}

unsigned int GameObject::getId() {
  return _id;
}

Transform GameObject::fullTransform() {
  if (_parent == nullptr) {
    return transform;
  }

  return transform.add(_parent->fullTransform());
}

std::string GameObject::getName() {
  return _name;
}


} /* hx3d */
