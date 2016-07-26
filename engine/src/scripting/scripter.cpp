#include "hx3d/scripting/scripter.hpp"

#include "hx3d/utils/log.hpp"

#include <cstdlib>

namespace hx3d {
namespace scripting {

Scripter::Scripter(std::string context_name) {
  _state = mrb_open();
  if (_state == nullptr) {
    Log.Error("Scripting: invalid mrb interpreter, exiting...");
    exit(1);
  }

  _context = mrbc_context_new(_state);
  _context->capture_errors = TRUE;
  _context->lineno = 1;

  mrbc_filename(_state, _context, std::string("(" + context_name + ")").c_str());

  Log.Debug("Scripting: scripter ready with context `%s`", context_name.c_str());
}

Scripter::~Scripter() {
  // mrbc_context_free(_state, _context);
  // mrb_close(_state);
}

void Scripter::add_global_variable(std::string name, mrb_value value) {
  mrb_define_global_const(_state, name.c_str(), value);
}

mrb_state* Scripter::get_state() const {
  return _state;
}

mrbc_context* Scripter::get_context() const {
  return _context;
}

} /* scripting */
} /* hx3d */
