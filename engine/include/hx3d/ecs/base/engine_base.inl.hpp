/*
    Entity Component System: Base EngineBase.
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

template <class EntityType>
EngineBase<EntityType>::EngineBase()
{
  static_assert(std::is_base_of<IDBase, EntityType>::value, "EntityType must be an IDBase.");
}

template <class EntityType>
Ptr<EntityType> EngineBase<EntityType>::createEntity() {
  Ptr<EntityType> entity(Make<EntityType>(lastEntityAvailable()));
  _entities[entity->getId()] = entity;
  _components[entity->getId()] = std::map<std::type_index, Ptr<Component>>();
  _bits[entity->getId()] = Bitset();

  return entity;
}

template <class EntityType>
void EngineBase<EntityType>::registerEntity(Ptr<EntityType> entity) {
  if (entity->getId() != 0) {
    Log.Error("EngineBase: entity `%d` already registered.", entity->getId());
    return;
  }

  entity->setId(lastEntityAvailable());
  _entities[entity->getId()] = entity;
  _components[entity->getId()] = std::map<std::type_index, Ptr<Component>>();
  _bits[entity->getId()] = Bitset();
}

template <class EntityType>
void EngineBase<EntityType>::removeEntity(Ptr<EntityType> entity) {
  _toRemove.push_back(entity->getId());
}

template <class EntityType>
unsigned int EngineBase<EntityType>::getComponentSize(Ptr<EntityType> entity) {
  if (_components.find(entity->getId()) == _components.end()) {
    Log.Error("No entity %ld", entity->getId());
    return 0;
  }

  std::map<std::type_index, Ptr<Component>>& compMap = _components[entity->getId()];
  return compMap.size();
}

template <class EntityType>
unsigned int EngineBase<EntityType>::getEntityCount() {
  return _entities.size();
}

template <class EntityType>
unsigned int EngineBase<EntityType>::getBits(Ptr<EntityType> entity) {
  unsigned int id = entity->getId();
  return _bits[id].getBits();
}

template <class EntityType>
void EngineBase<EntityType>::update(float delta) {
  for (auto& id: _entities) {
    for (auto& pair: _systems) {
      Ptr<SystemBase<EntityType>> sys = pair.second;
      if (sys->canProcess(_bits[id.first].getBits())) {
        sys->process(id.second, delta);
      }
    }
  }

  cleanEntities();
}

template <class EntityType>
void EngineBase<EntityType>::cleanEntities() {

  for (unsigned int i: _toRemove) {
    removeComponents(i);

    _bits.erase(i);
    _entities.erase(i);
  }

  _toRemove.clear();
}

template <class EntityType>
unsigned int EngineBase<EntityType>::lastEntityAvailable() {
  unsigned int first = 1;
  for (auto& pair: _entities) {
    if (pair.first != first)
      break;

    ++first;
  }

  return first;
}

template <class EntityType>
void EngineBase<EntityType>::removeComponents(unsigned int entityId) {

  if (_components.find(entityId) != _components.end()) {
    while (_components[entityId].size() > 0) {
      auto& comp = *(_components[entityId].begin());

      if (_onComponentRemoved.find(comp.first) != _onComponentRemoved.end()) {
        _onComponentRemoved[comp.first](comp.second, _entities[entityId]);
      }

      _components[entityId].erase(comp.first);
    }
  }
}

template <class EntityType>
void EngineBase<EntityType>::clear() {
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

template <class EntityType>
template <class T>
Ptr<T> EngineBase<EntityType>::getComponent(Ptr<EntityType> entity) {
  if (_components.find(entity->getId()) == _components.end()) {
    Log.Error("No entity %ld", entity->getId());
    return nullptr;
  }

  std::map<std::type_index, Ptr<Component>>& compMap = _components[entity->getId()];
  if (compMap.find(typeid(T)) == compMap.end()) {
    Log.Error("No component of type %s in entity %ld", typeid(T).name(), entity->getId());
    return nullptr;
  }

  Ptr<Component> component = compMap[typeid(T)];
  return std::dynamic_pointer_cast<T>(component);
}

template <class EntityType>
template <class T>
void EngineBase<EntityType>::addComponent(Ptr<EntityType> entity, Ptr<Component> component) {
  addInternalComponent<T>(entity->getId(), component);
}

template <class EntityType>
template <class T, class... Args>
void EngineBase<EntityType>::createComponent(Ptr<EntityType> entity, Args... args) {
  addInternalComponent<T>(entity->getId(), Make<T>(args...));
}

template <class EntityType>
template <class T>
void EngineBase<EntityType>::addInternalComponent(unsigned int entityId, Ptr<Component> component) {

  auto& type = typeid(T);

  if (_components.find(entityId) == _components.end()) {
    Log.Error("No entity %ld", entityId);
    return;
  }

  std::map<std::type_index, Ptr<Component>>& compMap = _components[entityId];

  // Already a component from this type
  if (compMap.find(type) != compMap.end()) {
    if (_onComponentRemoved.find(type) != _onComponentRemoved.end()) {
      _onComponentRemoved[type](compMap[type], _entities[entityId]);
    }
  }

  compMap[type] = component;

  _bits[entityId].set(ComponentBits::get<T>());

  if (_onComponentAdded.find(type) != _onComponentAdded.end()) {
    auto& func = _onComponentAdded[type];
    func(component, _entities[entityId]);
  }
}

template <class EntityType>
template <class T>
void EngineBase<EntityType>::addSystem(Ptr<SystemBase<EntityType>> sys) {
  auto& type = typeid(T);

  _systems[type] = sys;
  _systems[type]->_engine = this;
}

template <class EntityType>
template <class T, class... Args>
void EngineBase<EntityType>::createSystem(Args... args) {
  auto& type = typeid(T);

  _systems[type] = Make<T>(args...);
  _systems[type]->_engine = this;
}

template <class EntityType>
template <class T>
void EngineBase<EntityType>::registerComponentAdded(std::function<void(Ptr<Component>, Ptr<EntityType>)> callback) {
  _onComponentAdded[typeid(T)] = callback;
}

template <class EntityType>
template <class T>
void EngineBase<EntityType>::registerComponentRemoved(std::function<void(Ptr<Component>, Ptr<EntityType>)> callback) {
  _onComponentRemoved[typeid(T)] = callback;
}
