#include "hx3d/utils/yaml.hpp"
#include "hx3d/utils/file.hpp"

namespace hx3d {
namespace yaml {

YAML::Node loadFromFile(std::string pathToFile) {
  auto content = File::loadAsciiFile(pathToFile)->toString();
  auto rootNode = YAML::Load(content);

  return rootNode;
}

YAML::Node getNode(YAML::Node& node, std::string name) {
  return node[name];
}

} /* yaml */
} /* hx3d */
