#include "hx3d/utils/yaml.hpp"
#include "hx3d/utils/file.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace yaml {

YAML::Node loadFromFile(std::string pathToFile) {
  auto content = File::loadAsciiFile(pathToFile)->toString();
  std::string content_copy = content;
  auto rootNode = YAML::Load(content_copy);

  return rootNode;
}

YAML::Node getNode(YAML::Node& node, std::string name) {
  return node[name];
}

} /* yaml */
} /* hx3d */
