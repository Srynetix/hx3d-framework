/*
    Entity Component System: Node
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

#include "hx3d/ecs/node.hpp"

namespace hx3d {
namespace ecs {

Node::Node(const std::string name):
  Entity(0), _name(name), _parent(nullptr)
{}

Transform Node::getFullTransform() {
  if (_parent == nullptr) {
    return transform;
  }

  return transform.add(_parent->getFullTransform());
}

void Node::removeChild(SceneGraph& sg, const std::string name) {
  if (!childNameExists(name)) {
    Log.Error("Node: child `%s` does not exists.", name.c_str());
    return;
  }

  const Ptr<Node>& obj = getChild<Node>(name);
  sg.remove(obj->getPath());
}

std::string Node::getPath() {
  std::string path = _name;
  Ptr<Node> cursor = _parent;

  while (cursor != nullptr) {

    // Root
    if (cursor->_parent == nullptr) {
      path = "/" + path;
    }
    else {
      path = cursor->_name + "/" + path;
    }

    cursor = cursor->_parent;
  }

  return path;
}

void Node::draw(Batch& batch) {}

void Node::update(const float delta) {}

void Node::destroy(SceneGraph& sg) {
  sg.remove(getPath());
}

unsigned int Node::getChildCount() {

  unsigned int totalChildren = 0;
  for (auto& child: _children) {
    totalChildren += child->getChildCount();
  }

  return totalChildren + _children.size();
}

/////////////////////

bool Node::childNameExists(const std::string name) {
  for (const Ptr<Node>& o: _children) {
    if (o->_name == name) {
      return true;
    }
  }

  return false;
}

} /* ecs */
} /* hx3d */
