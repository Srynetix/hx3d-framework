namespace hx3d {
namespace yaml {

template <class Type>
Type Document::value(yaml_node_t* node, const std::string& str, Type defaultValue) {
  auto n = fetch(node, str);
  if (!n) return defaultValue;

  if (n->type == YAML_SCALAR_NODE) {
    return cast<Type>(n);
  } else {
    Log.Error("YAML node is not scalar. Can not fetch value.");
    return defaultValue;
  }
}

template <class Type>
Type Document::valueAtIndex(yaml_node_t* node, int idx, Type defaultType) {

  if (node->type == YAML_SEQUENCE_NODE) {
    auto list = listChildren(node);
    if (idx >= (int)list.size()) return defaultType;
    return cast<Type>(list[idx]);
  } else {
    Log.Error("YAML node is not sequence. Can not fetch index.");
    return defaultType;
  }
}

template <class ...Args>
yaml_node_t* Document::fetch(const std::string& str, Args... args) {
  return fetch(_root, str, args...);
}

template <class ...Args>
yaml_node_t* Document::fetch(yaml_node_t* node, const std::string& str, Args... args) {
  return fetch(_getChild(node, str), args...);
}

// template <class ...Args>
// yaml_node_t* Document::exists(yaml_node_t* node, const std::string& str, Args... args) {
//   return exists(_getChild(node, str), args...);
// }

template <class Type>
Type Document::cast(yaml_node_t* node) {
  std::istringstream iss((const char*)node->data.scalar.value);
  Type value;

  iss >> value;
  return value;
}

template <>
inline std::string Document::cast(yaml_node_t* node) {
  return std::string((const char*)node->data.scalar.value);
}

template <>
inline bool Document::cast(yaml_node_t* node) {
  std::string str = cast<std::string>(node);
  return (str == "True" || str == "true");
}

} /* yaml */
} /* hx3d */
