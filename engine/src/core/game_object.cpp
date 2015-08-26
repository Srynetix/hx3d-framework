/*
    Game Object.
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

#include "hx3d/core/game_object.hpp"

#include "hx3d/utils/log.hpp"

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
  _parent(parent.get()), _id(id), _name(name)
{}

GameObject::~GameObject()
{}

void GameObject::setParent(Ptr<GameObject> parent) {
  _parent = parent.get();
}

void GameObject::setParent(GameObject* parent) {
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

void GameObject::addChild(Ptr<GameObject> object) {
  if (object->getName() == "") {
    Log.Error("GameObject: you can't add a unnamed game object.");
    return;
  }

  object->setParent(this);
  _children.push_back(object);
}

std::vector<Ptr<GameObject>>& GameObject::getChildren() {
  return _children;
}

void GameObject::update()
{}

void GameObject::draw(Batch& batch)
{}

} /* hx3d */
