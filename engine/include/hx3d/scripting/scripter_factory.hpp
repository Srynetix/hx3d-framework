#pragma once

#include "hx3d/scripting/scripter.hpp"

namespace hx3d {
namespace scripting {

class ScripterFactory {
public:
  ScripterFactory(Scripter& scripter);

  mrb_value create_str(const std::string& string);

  std::string fetch_str(mrb_value value);

private:
  Scripter& _scripter;
};

} /* scripting */
} /* hx3d */
