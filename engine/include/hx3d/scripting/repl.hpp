#pragma once

#include <string>

#include <mruby.h>
#include <mruby/compile.h>

namespace hx3d {
namespace scripting {

class Scripter;

class REPL {
public:
  struct Config {
    std::string motd;
    Scripter* scripter;

    Config();
  };

  REPL(Config& wrapper);
  void start_auto();

  void begin();
  void end();

  //////////

  std::string show_prompt();
  std::string execute_line(std::string str);

  std::string _parse_current_code();

private:
  std::string _name;
  mrb_state* _state;
  mrbc_context* _context;
  Config _config;
  mrb_bool _code_block_open;
  const char* _utf8;

  void _show_value(mrb_value obj, int prompt);
  mrb_bool _is_code_block_open(mrb_parser_state* parser);
  void _print_hint();
  void _print_cmdline(int code_block_open);
  int _check_keyword(const char* buf, const char* word);
  std::string _show_value_str(mrb_value obj, int prompt);

  int _ai;
  mrb_bool _running;
  std::string _ruby_code;
  std::string _current_line;
};

} /* scripting */
} /* hx3d */
