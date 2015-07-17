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

template <class T>
Ptr<T> Engine::getComponent(Ptr<Entity> entity) {
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

template <class T>
void Engine::addComponent(Ptr<Entity> entity, Ptr<Component> component) {
  addInternalComponent<T>(entity->getId(), component);
}

template <class T, class... Args>
void Engine::createComponent(Ptr<Entity> entity, Args... args) {
  addInternalComponent<T>(entity->getId(), Make<T>(args...));
}

template <class T>
void Engine::addInternalComponent(unsigned int entityId, Ptr<Component> component) {

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

template <class T>
void Engine::addSystem(Ptr<System> sys) {
  auto& type = typeid(T);

  _systems[type] = sys;
  _systems[type]->_engine = this;
}

template <class T, class... Args>
void Engine::createSystem(Args... args) {
  auto& type = typeid(T);

  _systems[type] = Make<T>(args...);
  _systems[type]->_engine = this;
}

template <class T>
void Engine::registerComponentAdded(std::function<void(Ptr<Component>, Ptr<Entity>)> callback) {
  _onComponentAdded[typeid(T)] = callback;
}

template <class T>
void Engine::registerComponentRemoved(std::function<void(Ptr<Component>, Ptr<Entity>)> callback) {
  _onComponentRemoved[typeid(T)] = callback;
}
