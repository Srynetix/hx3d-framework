namespace hx3d {
namespace yaml {

template <class Type, class ...Args>
Type Document::fetch(const std::string& str, Args... args) {
  return fetch<Type>(_root, str, args...);
}

template <class Type, class ...Args>
Type Document::fetch(yaml_node_t* node, const std::string& str, Args... args) {
  auto n = fetchNode(node, str, args...);
  if (n->type == YAML_SCALAR_NODE) {
    return cast<Type>(n);
  } else {
    Log.Error("YAML node is not scalar. Can not fetch value.");
    return Type();
  }
}

template <class Type>
Type Document::fetchIndex(yaml_node_t* node, int idx) {
  if (node->type == YAML_SEQUENCE_NODE) {
    return cast<Type>(listChildren(node)[idx]);
  } else {
    Log.Error("YAML node is not sequence. Can not fetch index.");
    return Type();
  }
}

template <class ...Args>
yaml_node_t* Document::fetchNode(const std::string& str, Args... args) {
  return fetchNode(_root, str, args...);
}

template <class ...Args>
yaml_node_t* Document::fetchNode(yaml_node_t* node, const std::string& str, Args... args) {
  return fetchN(node, str, args...);
}

template <class ...Args>
yaml_node_t* Document::fetchN(yaml_node_t* node, const std::string& str, Args... args) {
  return fetchN(_getChild(node, str), args...);
}

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
