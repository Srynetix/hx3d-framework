#pragma once

// #include <yaml-cpp/yaml.h>
#include <string>
#include <yaml.h>
#include <sstream>
#include <vector>
// #include <utility>

/*
YAML:
  - fetch node from document using strs list
  - fetch node from other node using strs list
  - fetch value from node

*/

#include "hx3d/utils/file.hpp"
#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace yaml {

class Document {
public:
  Document(const std::string& pathToFile);
  ~Document();

  std::vector<yaml_node_t*> listChildren(yaml_node_t* node);
  std::vector<std::pair<std::string, yaml_node_t*>> listPairs(yaml_node_t* node);

  template <class Type>
  Type value(yaml_node_t* node, const std::string& str, Type defaultValue = Type());
  template <class Type>
  Type valueAtIndex(yaml_node_t* node, int idx, Type defaultValue = Type());

  bool exists(yaml_node_t* node, const std::string& str);

  template <class ...Args>
  yaml_node_t* fetch(const std::string& str, Args... args);
  template <class ...Args>
  yaml_node_t* fetch(yaml_node_t* node, const std::string& str, Args... args);
  yaml_node_t* fetch(yaml_node_t* node, const std::string& str);

  template <class Type>
  Type cast(yaml_node_t* node);

private:
  yaml_node_t* _getChild(yaml_node_t* node, const std::string& name);

  yaml_node_t* _root;
  yaml_document_t _document;
};

} /* yaml */
} /* hx3d */

#include "hx3d/utils/_inline/yaml.inl.hpp"
