#pragma once

#include <yaml-cpp/yaml.h>

namespace hx3d {
namespace yaml {

YAML::Node loadFromFile(std::string pathToFile);
YAML::Node getNode(YAML::Node& node, std::string name);

template <class T>
T getValue(YAML::Node& node, std::string name, T defaultValue = T());

template <class T>
T getListValue(YAML::Node& node, int i, T defaultValue = T());

} /* yaml */
} /* hx3d */

#include "hx3d/utils/_inline/yaml.inl.hpp"
