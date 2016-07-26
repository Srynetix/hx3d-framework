#pragma once

// #include <yaml-cpp/yaml.h>
#include <string>
#include <yaml.h>
#include <sstream>
#include <vector>
// #include <utility>

#include "hx3d/utils/file.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace yaml {

class Document {
public:
  Document();
  ~Document();

  static Document loadFromFile(const std::string& pathToFile);

  std::vector<yaml_node_t*> listChildren(yaml_node_t* node);
  std::vector<std::pair<std::string, yaml_node_t*>> listPairs(yaml_node_t* node);

  template <class Type>
  Type cast(yaml_node_t* node);

  template <class Type, class ...Args>
  Type fetch(const std::string& str, Args... args);
  template <class Type, class ...Args>
  Type fetch(yaml_node_t* node, const std::string& str, Args... args);

  template <class Type>
  Type fetchIndex(yaml_node_t* node, int idx);

  template <class ...Args>
  yaml_node_t* fetchNode(const std::string& str, Args... args);
  template <class ...Args>
  yaml_node_t* fetchNode(yaml_node_t* node, const std::string& str, Args... args);

  template <class ...Args>
  yaml_node_t* fetchN(yaml_node_t* node, const std::string& str, Args... args);
  yaml_node_t* fetchN(yaml_node_t* node, const std::string& str);

private:
  yaml_node_t* _getChild(yaml_node_t* node, const std::string& name);

  yaml_node_t* _root;
  yaml_document_t _document;
};

} /* yaml */
} /* hx3d */

#include "hx3d/utils/_inline/yaml.inl.hpp"
