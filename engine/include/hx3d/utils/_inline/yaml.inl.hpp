namespace hx3d {
namespace yaml {

template <class T>
T getValue(YAML::Node& node, std::string name, T defaultValue) {
  if (node[name]) {
    return node[name].as<T>();
  }

  return defaultValue;
}

template <class T>
T getListValue(YAML::Node& node, int i, T defaultValue) {
  if (node[i]) {
    return node[i].as<T>();
  }

  return defaultValue;
}

} /* yaml */
} /* hx3d */
