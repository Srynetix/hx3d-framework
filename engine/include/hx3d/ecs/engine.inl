/*
    Entity Component System: Engine.
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

template <class E>
Engine<E>::Engine()
{}

template <class E>
Ptr<E> Engine<E>::createEntity() {
  Ptr<E> entity(Make<E>(lastEntityAvailable()));
  _entities[entity->getId()] = entity;
  _components[entity->getId()] = std::map<std::type_index, Ptr<Component>>();
  _bits[entity->getId()] = Bitset();

  return entity;
}

template <class E>
void Engine<E>::registerEntity(Ptr<E> entity) {
  if (entity->getId() != 0) {
    Log.Error("Engine: entity `%d` already registered.", entity->getId());
    return;
  }

  entity->setId(lastEntityAvailable());
  _entities[entity->getId()] = entity;
  _components[entity->getId()] = std::map<std::type_index, Ptr<Component>>();
  _bits[entity->getId()] = Bitset();
}

template <class E>
void Engine<E>::removeEntity(Ptr<E> entity) {
  _toRemove.push_back(entity->getId());
}

template <class E>
unsigned int Engine<E>::getComponentSize(Ptr<E> entity) {
  if (_components.find(entity->getId()) == _components.end()) {
    Log.Error("No entity %ld", entity->getId());
    return 0;
  }

  std::map<std::type_index, Ptr<Component>>& compMap = _components[entity->getId()];
  return compMap.size();
}

template <class E>
unsigned int Engine<E>::getBits(Ptr<E> entity) {
  unsigned int id = entity->getId();
  return _bits[id].getBits();
}

template <class E>
void Engine<E>::update() {
  for (auto& id: _entities) {
    for (auto& pair: _systems) {
      Ptr<System<E>> sys = pair.second;
      if (sys->canProcess(_bits[id.first].getBits())) {
        sys->process(Make<E>(id.first));
      }
    }
  }

  cleanEntities();
}

template <class E>
void Engine<E>::cleanEntities() {

  for (unsigned int i: _toRemove) {
    removeComponents(i);

    _bits.erase(i);
    _entities.erase(i);
  }

  _toRemove.clear();
}

template <class E>
unsigned int Engine<E>::lastEntityAvailable() {
  unsigned int first = 1;
  for (auto& pair: _entities) {
    if (pair.first != first)
      break;

    ++first;
  }

  return first;
}

template <class E>
void Engine<E>::removeComponents(unsigned int entityId) {

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

template <class E>
void Engine<E>::clear() {
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

template <class E>
template <class T>
Ptr<T> Engine<E>::getComponent(Ptr<E> entity) {
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

template <class E>
template <class T>
void Engine<E>::addComponent(Ptr<E> entity, Ptr<Component> component) {
  addInternalComponent<T>(entity->getId(), component);
}

template <class E>
template <class T, class... Args>
void Engine<E>::createComponent(Ptr<E> entity, Args... args) {
  addInternalComponent<T>(entity->getId(), Make<T>(args...));
}

template <class E>
template <class T>
void Engine<E>::addInternalComponent(unsigned int entityId, Ptr<Component> component) {

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

template <class E>
template <class T>
void Engine<E>::addSystem(Ptr<System<E>> sys) {
  auto& type = typeid(T);

  _systems[type] = sys;
  _systems[type]->_engine = this;
}

template <class E>
template <class T, class... Args>
void Engine<E>::createSystem(Args... args) {
  auto& type = typeid(T);

  _systems[type] = Make<T>(args...);
  _systems[type]->_engine = this;
}

template <class E>
template <class T>
void Engine<E>::registerComponentAdded(std::function<void(Ptr<Component>, Ptr<E>)> callback) {
  _onComponentAdded[typeid(T)] = callback;
}

template <class E>
template <class T>
void Engine<E>::registerComponentRemoved(std::function<void(Ptr<Component>, Ptr<E>)> callback) {
  _onComponentRemoved[typeid(T)] = callback;
}
