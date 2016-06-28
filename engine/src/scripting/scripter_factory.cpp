#include "hx3d/scripting/scripter_factory.hpp"

#include <mruby/value.h>
#include <mruby/string.h>

namespace hx3d {
namespace scripting {

ScripterFactory::ScripterFactory(Scripter& scripter): _scripter(scripter) {}

mrb_value ScripterFactory::create_str(const std::string& string) {
  return mrb_str_new_cstr(_scripter.get_state(), string.c_str());
}

std::string ScripterFactory::fetch_str(mrb_value value) {
  if (mrb_string_p(value)) {
    // char* res = malloc(RSTRING_LEN(value) + 1);
    char* res = mrb_str_to_cstr(_scripter.get_state(), value);
    return res;
  }

  else {
    std::cerr << "No STR !" << std::endl;
    exit(1);
  }
}

} /* scripting */
} /* hx3d */
