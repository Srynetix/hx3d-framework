#pragma once

#include "tests/screens/base_test_screen.hpp"
#include "hx3d/scripting/scripter.hpp"
#include "hx3d/scripting/repl.hpp"

#include "hx3d/gui/panel.hpp"
#include "hx3d/gui/textbox.hpp"
#include "hx3d/gui/label.hpp"
#include "hx3d/gui/system.hpp"

#include "hx3d/utils/log.hpp"
#include "hx3d/math/number_utils.hpp"

#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/text.hpp"
#include "hx3d/graphics/batches/simple_batch_2d.hpp"
#include "hx3d/graphics/cameras/orthographic_camera.hpp"

// #include <string>

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::scripting;
using namespace hx3d::gui;

class ConsolePanel: public Panel {
public:
  ConsolePanel(const Pointer<Widget>& widget = nullptr): Panel(widget) {
    _visible = false;
  }
};

class ConsoleTextBox: public TextBox {
public:
  ConsoleTextBox(const Pointer<Widget>& widget = nullptr): TextBox(widget) {
    _historyPos = 0;
  }

  virtual void keyPressed(KeyEvent::Key key) override {
    // Up
    if (key == KeyEvent::Key::Up) {
      if (_history.size() > 0) {
        _historyPos = math::modulo(_historyPos - 1, _history.size());
        setText(_history[_historyPos]);
      }
    }

    // Down
    else if (key == KeyEvent::Key::Down) {
      if (_history.size() > 0) {
        _historyPos = math::modulo(_historyPos + 1, _history.size());
        setText(_history[_historyPos]);
      }
    }

    // History OK
    else if (key == KeyEvent::Key::Return) {
      auto Log = Logger::getLogger("tests");

      if (_content != "") {
        _history.push_back(_content);
        _historyPos = _history.size();
      }
    }

    TextBox::keyPressed(key);
  }

  std::vector<std::string> _history;
  int _historyPos;
};

class ConsoleBuffer: public Label {
public:
  ConsoleBuffer(const Pointer<Widget>& widget = nullptr): Label(widget) {}
};

/*******************
  Test
********************/

class Test21: public BaseTestScreen {
public:
  Test21();

  virtual void update(float delta) override;
  virtual void render() override;

  virtual void onKeyPressed(KeyEvent::Key key) override;

private:
  Text::Ref text;
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch2D::Ref batch;

  Scripter scripter;
  Pointer<System> gui;
  Pointer<REPL> repl;
  Pointer<ConsolePanel> console;
};
