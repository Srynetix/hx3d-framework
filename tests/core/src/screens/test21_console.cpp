#include "tests/screens/test21_console.hpp"

// #include "hx3d/scripting/scripter.hpp"
// #include "hx3d/scripting/repl.hpp"
//
// #include "hx3d/gui/panel.hpp"
// #include "hx3d/gui/textbox.hpp"
// #include "hx3d/gui/label.hpp"
// #include "hx3d/gui/placement.hpp"
// #include "hx3d/gui/system.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"
#include "hx3d/graphics/framebuffer.hpp"

Test21::Test21()
{
  batch->setCamera(camera);

  REPL::Config config;
  config.scripter = &scripter;
  repl = Make<REPL>(config);
  repl->begin();

  console = Make<ConsolePanel>();
  auto textbox = Make<ConsoleTextBox>();
  auto buffer = Make<ConsoleBuffer>();

  text->setPosition(Core::App()->getWidth() / 2, Core::App()->getHeight() / 2);
  text->setContent("Press ²");

  gui = Make<System>(Placement::Relative(console, {0.5, 0.5}, {1, 0.5}).apply());
  // gui = Make<System>(console);
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

void Test21::update(float delta) {
  camera->update();

  gui->update(delta);
}

void Test21::render() {
  Framebuffer::clear(Color::Black);

  batch->begin();
  batch->draw(text);
  gui->draw(batch);
  batch->end();
}

void Test21::onKeyPressed(KeyEvent::Key key) {
  BaseTestScreen::onKeyPressed(key);

  if (key == KeyEvent::Key::ConsoleKey || key == KeyEvent::Key::AndroidMenu) {
    if (console->isVisible()) {
      gui->exitFocus();
      console->hide();
      console->exitFocus();
    }

    else {
      gui->enterFocus();
      console->show();
      console->enterFocus();
    }
  }
}
