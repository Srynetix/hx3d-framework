#include "./base_test_screen.hpp"
#include "hx3d/scripting/scripter.hpp"
#include "hx3d/scripting/repl.hpp"

#include "hx3d/gui/panel.hpp"
#include "hx3d/gui/textbox.hpp"
#include "hx3d/gui/label.hpp"
#include "hx3d/gui/placement.hpp"
#include "hx3d/gui/system.hpp"

#include <string>

using namespace hx3d;
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
  ConsoleTextBox(const Pointer<Widget>& widget = nullptr): TextBox(widget) {}
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
  Test21()
  {
    batch->setCamera(camera);

    REPL::Config config;
    config.scripter = &scripter;
    repl = Make<REPL>(config);
    repl->begin();

    console = Make<ConsolePanel>();
    auto textbox = Make<ConsoleTextBox>();
    auto buffer = Make<ConsoleBuffer>();

    text->transform.position.x = Core::App()->getWidth() / 2;
    text->transform.position.y = Core::App()->getHeight() / 2;
    text->setContent("Press ²");

    gui = Make<System>(Placement::Relative(console, {0.5, 0.5}, {0.5, 0.5}).apply());
    console->addChild(Placement::Relative(buffer, {0.5, 0.25}, {0.75, 0.1}));
    console->addChild(Placement::Relative(textbox, {0.5, 0.75}, {0.75, 0.1}));

    textbox->on("validate", [this,textbox,buffer]() {
      auto txt = textbox->getText();
      if (txt.size() > 0) {
        std::string ret = repl->execute_line(txt);
        textbox->setText("");
        buffer->setText(ret);
      }
    });

    gui->update(1/60.f);
  }

  virtual void dispose() {
    repl->end();
  }

  virtual void update(float delta) override {
    camera->update();

    gui->update(delta);
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    batch->begin();
    batch->draw(text);
    gui->draw(batch);
    batch->end();
  }

  virtual void onKeyPressed(KeyEvent::Key key) {
    BaseTestScreen::onKeyPressed(key);

    if (key == KeyEvent::Key::ConsoleKey) {
      if (console->isVisible()) {
        gui->exitFocus();
        console->hide();
        console->exitFocus();
      }

      else {
        Log.Info("SHOW");
        gui->enterFocus();
        console->show();
        console->enterFocus();
      }
    }
  }

private:
  Text::Ref text;

  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch2D::Ref batch;
  Scripter scripter;
  System::Ptr gui;
  Pointer<REPL> repl;
  Pointer<ConsolePanel> console;
};
