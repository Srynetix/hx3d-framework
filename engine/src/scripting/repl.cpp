#include "hx3d/scripting/repl.hpp"

#include "hx3d/scripting/scripter.hpp"

#include <iostream>
#include <sstream>
#include <cstring>
#include <csignal>
#include <cstdlib>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/proc.h>
#include <mruby/compile.h>
#include <mruby/string.h>

namespace hx3d {
namespace scripting {

REPL::Config::Config() {
  motd = "Welcome to mIRB.";
  scripter = nullptr;
}

REPL::REPL(Config& config) {
  _config = config;
  _context = config.scripter->get_context();
  _state = config.scripter->get_state();
  _code_block_open = FALSE;
}

REPL::~REPL() {
  
}

void REPL::_show_value(mrb_value obj, int prompt)
{
  mrb_value val;

  val = mrb_funcall(_state, obj, "inspect", 0);
  if (prompt) {
    if (!_state->exc) {
      std::cout << " => ";
    }
    else {
      val = mrb_funcall(_state, mrb_obj_value(_state->exc), "inspect", 0);
    }
  }
  if (!mrb_string_p(val)) {
    val = mrb_obj_as_string(_state, obj);
  }
  std::cout << RSTRING_PTR(val) << std::endl;
}

std::string REPL::_show_value_str(mrb_value obj, int prompt)
{
  std::ostringstream oss;
  mrb_value val;

  val = mrb_funcall(_state, obj, "inspect", 0);
  if (prompt) {
    if (!_state->exc) {
      oss << " => ";
    }
    else {
      val = mrb_funcall(_state, mrb_obj_value(_state->exc), "inspect", 0);
    }
  }
  if (!mrb_string_p(val)) {
    val = mrb_obj_as_string(_state, obj);
  }
  oss << RSTRING_PTR(val) << std::endl;
  return oss.str();
}

/* Guess if the user might want to enter more
 * or if he wants an evaluation of his code now */
mrb_bool REPL::_is_code_block_open(mrb_parser_state *parser)
{
  mrb_bool code_block_open = FALSE;

  /* check for heredoc */
  if (parser->parsing_heredoc != NULL) return TRUE;
  if (parser->heredoc_end_now) {
    parser->heredoc_end_now = FALSE;
    return FALSE;
  }

  /* check for unterminated string */
  if (parser->lex_strterm) return TRUE;

  /* check if parser error are available */
  if (0 < parser->nerr) {
    const char unexpected_end[] = "syntax error, unexpected $end";
    const char *message = parser->error_buffer[0].message;

    /* a parser error occur, we have to check if */
    /* we need to read one more line or if there is */
    /* a different issue which we have to show to */
    /* the user */

    if (strncmp(message, unexpected_end, sizeof(unexpected_end) - 1) == 0) {
      code_block_open = TRUE;
    }
    else if (strcmp(message, "syntax error, unexpected keyword_end") == 0) {
      code_block_open = FALSE;
    }
    else if (strcmp(message, "syntax error, unexpected tREGEXP_BEG") == 0) {
      code_block_open = FALSE;
    }
    return code_block_open;
  }

  switch (parser->lstate) {

  /* all states which need more code */

  case EXPR_BEG:
    /* beginning of a statement, */
    /* that means previous line ended */
    code_block_open = FALSE;
    break;
  case EXPR_DOT:
    /* a message dot was the last token, */
    /* there has to come more */
    code_block_open = TRUE;
    break;
  case EXPR_CLASS:
    /* a class keyword is not enough! */
    /* we need also a name of the class */
    code_block_open = TRUE;
    break;
  case EXPR_FNAME:
    /* a method name is necessary */
    code_block_open = TRUE;
    break;
  case EXPR_VALUE:
    /* if, elsif, etc. without condition */
    code_block_open = TRUE;
    break;

  /* now all the states which are closed */

  case EXPR_ARG:
    /* an argument is the last token */
    code_block_open = FALSE;
    break;

  /* all states which are unsure */

  case EXPR_CMDARG:
    break;
  case EXPR_END:
    /* an expression was ended */
    break;
  case EXPR_ENDARG:
    /* closing parenthese */
    break;
  case EXPR_ENDFN:
    /* definition end */
    break;
  case EXPR_MID:
    /* jump keyword like break, return, ... */
    break;
  case EXPR_MAX_STATE:
    /* don't know what to do with this token */
    break;
  default:
    /* this state is unexpected! */
    break;
  }

  return code_block_open;
}

/* Print a short remark for the user */
void REPL::_print_hint()
{
  std::cout << _config.motd << std::endl << std::endl;
}

/* Print the command line prompt of the REPL */
void REPL::_print_cmdline(int code_block_open)
{
  if (code_block_open) {
    std::cout << "* ";
  }
  else {
    std::cout << "> ";
  }

  std::cout.flush();
}

std::string REPL::show_prompt() {

  std::ostringstream oss;

  if (_code_block_open) {
    oss << "* ";
  } else {
    oss << "> ";
  }

  return oss.str();
}

int REPL::_check_keyword(const char *buf, const char *word)
{
  const char *p = buf;
  size_t len = strlen(word);

  /* skip preceding spaces */
  while (*p && isspace((unsigned char)*p)) {
    p++;
  }
  /* check keyword */
  if (strncmp(p, word, len) != 0) {
    return 0;
  }
  p += len;
  /* skip trailing spaces */
  while (*p) {
    if (!isspace((unsigned char)*p)) return 0;
    p++;
  }
  return 1;
}

volatile sig_atomic_t input_canceled = 0;
void ctrl_c_handler(int signo)
{
  (void)signo;
  input_canceled = 1;
}

void REPL::begin() {
  _ai = mrb_gc_arena_save(_state);
  _running = TRUE;
}

void REPL::end() {
  _running = FALSE;
}

std::string REPL::execute_line(std::string line) {

  std::string result;
  _current_line = line + "\n";

  if (_code_block_open) {
    _ruby_code += _current_line;
  }

  else {
    if (_check_keyword(_current_line.c_str(), "quit") || _check_keyword(_current_line.c_str(), "exit")) {
      _running = FALSE;
      result = "exiting...";
    }

    else {
      _ruby_code += _current_line;
    }
  }

  _utf8 = mrb_utf8_from_locale(_ruby_code.c_str(), -1);
  if (!_utf8) abort();

  return _parse_current_code();
}

std::string REPL::_parse_current_code() {
  /* parse code */
  auto parser = mrb_parser_new(_state);
  if (parser == NULL) {
    return "create parser state error\n";
  }

  std::ostringstream oss;
  std::string str = "";

  parser->s = _utf8;
  parser->send = _utf8 + strlen(_utf8);
  parser->lineno = _context->lineno;
  mrb_parser_parse(parser, _context);
  _code_block_open = _is_code_block_open(parser);
  mrb_utf8_free(_utf8);

  if (_code_block_open) {
    /* no evaluation of code */
    return "* ";
  }
  else {
    if (0 < parser->nerr) {
      /* syntax error */
      oss << "line " << parser->error_buffer[0].lineno << ": " << parser->error_buffer[0].message << "\n";
      return oss.str();
    }
    else {
      /* generate bytecode */
      RProc *proc = mrb_generate_code(_state, parser);
      if (proc == NULL) {
        oss << "codegen error\n";
        mrb_parser_free(parser);
        return oss.str();
      }

      /* pass a proc for evaulation */
      /* evaluate the bytecode */
      auto stack_keep = proc->body.irep->nlocals;
      auto result = mrb_vm_run(_state,
          proc,
          mrb_top_self(_state),
          stack_keep);
      /* did an exception occur? */
      if (_state->exc) {
        str = _show_value_str(mrb_obj_value(_state->exc), 0);
        _state->exc = 0;
      }
      else {
        /* no */
        if (!mrb_respond_to(_state, result, mrb_intern_lit(_state, "inspect"))){
          result = mrb_any_to_s(_state, result);
        }
        str = _show_value_str(result, 1);
      }
    }

    _ruby_code = "";
    _current_line = "";
    mrb_gc_arena_restore(_state, _ai);
  }

  mrb_parser_free(parser);
  _context->lineno++;

  return str;
}

void REPL::start_auto()
{
  char ruby_code[4096] = { 0 };
  char last_code_line[1024] = { 0 };
  int last_char;
  size_t char_index;

  mrb_parser_state *parser;
  mrb_value result;
  mrb_bool code_block_open = FALSE;
  int ai;
  unsigned int stack_keep = 0;

  _print_hint();
  ai = mrb_gc_arena_save(_state);

  while (TRUE) {
    char *utf8;

    _print_cmdline(code_block_open);
    signal(SIGINT, ctrl_c_handler);

    char_index = 0;
    while ((last_char = getchar()) != '\n') {
      if (last_char == EOF) break;
      if (char_index > sizeof(last_code_line)-2) {
        std::cerr << "input string too long\n";
        continue;
      }
      last_code_line[char_index++] = last_char;
    }

    signal(SIGINT, SIG_DFL);
    if (input_canceled) {
      ruby_code[0] = '\0';
      last_code_line[0] = '\0';
      code_block_open = FALSE;
      puts("^C");
      input_canceled = 0;
      continue;
    }
    if (last_char == EOF) {
      std::cout << std::endl;
      break;
    }

    last_code_line[char_index++] = '\n';
    last_code_line[char_index] = '\0';

    if (code_block_open) {
      if (strlen(ruby_code)+strlen(last_code_line) > sizeof(ruby_code)-1) {
        std::cerr << "concatenated input string too long\n";
        continue;
      }
      strcat(ruby_code, last_code_line);
    }
    else {
      if (_check_keyword(last_code_line, "quit") || _check_keyword(last_code_line, "exit")) {
        break;
      }
      strcpy(ruby_code, last_code_line);
    }

    utf8 = mrb_utf8_from_locale(ruby_code, -1);
    if (!utf8) abort();

    /* parse code */
    parser = mrb_parser_new(_state);
    if (parser == NULL) {
      std::cerr << "create parser state error\n";
      break;
    }
    parser->s = utf8;
    parser->send = utf8 + strlen(utf8);
    parser->lineno = _context->lineno;
    mrb_parser_parse(parser, _context);
    code_block_open = _is_code_block_open(parser);
    mrb_utf8_free(utf8);

    if (code_block_open) {
      /* no evaluation of code */
    }
    else {
      if (0 < parser->nerr) {
        /* syntax error */
        std::cout << "line " << parser->error_buffer[0].lineno << ": " << parser->error_buffer[0].message << "\n";
      }
      else {
        /* generate bytecode */
        RProc *proc = mrb_generate_code(_state, parser);
        if (proc == NULL) {
          std::cerr << "codegen error\n";
          mrb_parser_free(parser);
          break;
        }

        /* pass a proc for evaulation */
        /* evaluate the bytecode */
        result = mrb_vm_run(_state,
            proc,
            mrb_top_self(_state),
            stack_keep);
        stack_keep = proc->body.irep->nlocals;
        /* did an exception occur? */
        if (_state->exc) {
          _show_value(mrb_obj_value(_state->exc), 0);
          _state->exc = 0;
        }
        else {
          /* no */
          if (!mrb_respond_to(_state, result, mrb_intern_lit(_state, "inspect"))){
            result = mrb_any_to_s(_state, result);
          }
          _show_value(result, 1);
        }
      }

      ruby_code[0] = '\0';
      last_code_line[0] = '\0';
      mrb_gc_arena_restore(_state, ai);
    }

    mrb_parser_free(parser);
    _context->lineno++;
  }
}


} /* scripting */
} /* hx3d */
