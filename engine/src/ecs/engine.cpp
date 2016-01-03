/*
    Engine.
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

#include "hx3d/ecs/engine.hpp"

namespace hx3d {
namespace ecs {

Engine::Engine() {}

Ptr<Entity> Engine::createEntity() {
  Ptr<Entity> entity(Make<Entity>(lastEntityAvailable()));
  _entities[entity->getId()] = entity;
  _components[entity->getId()] = std::map<std::type_index, Ptr<Component>>();
  _bits[entity->getId()] = Bitset();

  return entity;
}

void Engine::registerEntity(const Ptr<Entity>& entity) {
  if (entity->getId() != 0) {
    Log.Error("Engine: entity `%d` already registered.", entity->getId());
    return;
  }

  entity->setId(lastEntityAvailable());
  _entities[entity->getId()] = entity;
  _components[entity->getId()] = std::map<std::type_index, Ptr<Component>>();
  _bits[entity->getId()] = Bitset();
}

void Engine::removeEntity(const Ptr<Entity>& entity) {
  _toRemove.push_back(entity->getId());
}

unsigned int Engine::getComponentSize(const Ptr<Entity>& entity) {
  if (_components.find(entity->getId()) == _components.end()) {
    Log.Error("No entity %ld", entity->getId());
    return 0;
  }

  const std::map<std::type_index, Ptr<Component>>& compMap = _components[entity->getId()];
  return compMap.size();
}

unsigned int Engine::getEntityCount() {
  return _entities.size();
}

unsigned int Engine::getBits(const Ptr<Entity>& entity) {
  const unsigned int id = entity->getId();
  return _bits[id].getBits();
}

void Engine::update(const float delta) {
  for (auto& id: _entities) {
    for (auto& pair: _systems) {
      const Ptr<System>& sys = pair.second;
      if (sys->canProcess(_bits[id.first].getBits())) {
        sys->process(id.second, delta);
      }
    }
  }

  cleanEntities();
}

void Engine::cleanEntities() {
  for (const unsigned int i: _toRemove) {
    removeComponents(i);

    _bits.erase(i);
    _entities.erase(i);
  }

  _toRemove.clear();
}

unsigned int Engine::lastEntityAvailable() {
  unsigned int first = 1;
  for (auto& pair: _entities) {
    if (pair.first != first)
      break;

    ++first;
  }

  return first;
}

void Engine::removeComponents(const unsigned int entityId) {
  if (_components.find(entityId) != _components.end()) {
    while (_components[entityId].size() > 0) {
      const auto& comp = *(_components[entityId].begin());

      if (_onComponentRemoved.find(comp.first) != _onComponentRemoved.end()) {
        _onComponentRemoved[comp.first](comp.second, _entities[entityId]);
      }

      _components[entityId].erase(comp.first);
    }
  }
}

void Engine::clear() {
  for (auto& entity: _entities) {
    removeComponents(entity.first);
  }

  _components.clear();
  _bits.clear();
  _toRemove.clear();
  _entities.clear();

  _systems.clear();

  _onComponentAdded.clear();
  _onComponentRemoved.clear();
}

} /* ecs */
} /* hx3d */
