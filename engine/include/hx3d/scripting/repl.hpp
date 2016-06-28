#pragma once

#include <string>
#include <mruby.h>
#include <mruby/compile.h>

#include "hx3d/scripting/scripter.hpp"

namespace hx3d {
namespace scripting {

class REPL {
public:
  struct Config {
    std::string motd;
    Scripter* scripter;

    Config() {
      motd = "Welcome to mIRB.";
      scripter = nullptr;
    }
  };

  REPL(Config wrapper);
  void start();

private:
  std::string _name;
  mrb_state* _state;
  mrbc_context* _context;
  Config _config;

  void _show_value(mrb_value obj, int prompt);
  mrb_bool _is_code_block_open(mrb_parser_state* parser);
  void _print_hint();
  void _print_cmdline(int code_block_open);
  int _check_keyword(const char* buf, const char* word);
};

} /* scripting */
} /* hx3d */
