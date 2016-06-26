#pragma once

#include "hx3d/utils/file.hpp"
#include <yaml-cpp/yaml.h>

namespace hx3d {
namespace yaml {

YAML::Node loadFromFile(std::string pathToFile) {
  auto content = File::loadAsciiFile(pathToFile)->toString();
  auto rootNode = YAML::Load(content);

  return rootNode;
}

template <class T>
T getValue(YAML::Node& node, std::string name, T defaultValue = T()) {
  if (node[name]) {
    return node[name].template as<T>();
  }

  return defaultValue;
}

template <class T>
T getListValue(YAML::Node& node, int i, T defaultValue = T()) {
  if (node[i]) {
    return node[i].template as<T>();
  }

  return defaultValue;
}

YAML::Node getNode(YAML::Node& node, std::string name) {
  return node[name];
}

} /* yaml */
} /* hx3d */
