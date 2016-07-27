#include "hx3d/utils/yaml.hpp"

#include <utility>

namespace hx3d {
namespace yaml {

Document::Document(const std::string& pathToFile) {
  std::string content = File::loadAsciiFile(pathToFile)->toString();
  yaml_parser_t parser;

  yaml_parser_initialize(&parser);
  yaml_parser_set_input_string(&parser, (const unsigned char*)content.c_str(), content.size());
  yaml_parser_load(&parser, &(_document));

  _root = yaml_document_get_root_node(&(_document));
}

Document::~Document() {}

yaml_node_t* Document::_getChild(yaml_node_t* node, const std::string& name) {
  if (node->type == YAML_MAPPING_NODE) {
    for (int i = 0; i < (node->data.mapping.pairs.top - node->data.mapping.pairs.start); i++) {
      auto key_node = yaml_document_get_node(&_document, node->data.mapping.pairs.start[i].key);
      if (key_node->type == YAML_SCALAR_NODE) {
        auto key_node_name = std::string((const char *)key_node->data.scalar.value);

        if (key_node_name == name) {
          return yaml_document_get_node(&_document, node->data.mapping.pairs.start[i].value);
        }
      }
    }

    return nullptr;

  } else {
    auto Log = Logger::getLogger("utils");
    Log.Error("YAML Node is not a mapping node.");
    return nullptr;
  }
}

bool Document::exists(yaml_node_t* node, const std::string& name) {
  if (node->type == YAML_MAPPING_NODE) {
    for (int i = 0; i < (node->data.mapping.pairs.top - node->data.mapping.pairs.start); i++) {
      auto key_node = yaml_document_get_node(&_document, node->data.mapping.pairs.start[i].key);
      if (key_node->type == YAML_SCALAR_NODE) {
        auto key_node_name = std::string((const char *)key_node->data.scalar.value);

        if (key_node_name == name) {
          return true;
        }
      }
    }
  } else {
    auto Log = Logger::getLogger("utils");
    Log.Error("YAML Node is not a mapping node.");
  }

  return false;
}

yaml_node_t* Document::fetch(yaml_node_t* node, const std::string& str) {
  return _getChild(node, str);
}

std::vector<std::pair<std::string, yaml_node_t*>> Document::listPairs(yaml_node_t* node) {
  std::vector<std::pair<std::string, yaml_node_t*>> vec;

  if (node->type == YAML_MAPPING_NODE) {

    for (int i = 0; i < (node->data.mapping.pairs.top - node->data.mapping.pairs.start); i++) {
      auto key_node = yaml_document_get_node(&_document, node->data.mapping.pairs.start[i].key);
      if (key_node->type == YAML_SCALAR_NODE) {
        auto key_node_name = std::string((const char *)key_node->data.scalar.value);

        auto value_node = yaml_document_get_node(&_document, node->data.mapping.pairs.start[i].value);

        vec.push_back(std::make_pair(key_node_name, value_node));
      }
    }

  } else {
    auto Log = Logger::getLogger("utils");
    Log.Error("YAML Node is not a sequence node");
  }

  return vec;
}

std::vector<yaml_node_t*> Document::listChildren(yaml_node_t* node) {
  std::vector<yaml_node_t*> vec;

  if (node->type == YAML_SEQUENCE_NODE) {
    for (int i = 0; i < (node->data.sequence.items.top - node->data.sequence.items.start); i++) {
      auto child = yaml_document_get_node(&_document, node->data.sequence.items.start[i]);
      vec.push_back(child);
    }

  } else {
    auto Log = Logger::getLogger("utils");
    Log.Error("YAML Node is not a sequence node");
  }

  return vec;
}

} /* yaml */
} /* hx3d */
