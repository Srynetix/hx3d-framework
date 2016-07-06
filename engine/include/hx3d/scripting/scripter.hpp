#pragma once

#include <string>

#include <mruby.h>
#include <mruby/compile.h>

namespace hx3d {
namespace scripting {

class Scripter {
public:
  Scripter(std::string context_name = "hx3d");
  ~Scripter();

  void add_global_variable(std::string name, mrb_value value);

  mrb_state* get_state() const;
  mrbc_context* get_context() const;

private:
  mrb_state* _state;
  mrbc_context* _context;
};

} /* scripting */
} /* hx3d */
