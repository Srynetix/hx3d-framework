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

    auto panel = Make<Panel>();
    auto textbox = Make<TextBox>();
    auto label = Make<Label>();

    gui = Make<System>(Placement::Fill<Panel>(panel));
    // gui = Make<System>(Placement::Relative<Panel>(panel, {0.5, 0.75}, {1, 0.25}));
    panel->addChild(Placement::Relative<Label>(label, {0.75, 0.75}, {0.5, 0.15}));
    panel->addChild(Placement::Relative<TextBox>(textbox, {0.5, 0.25}, {0.95, 0.15}));

    // auto consolepanel = gui->getContent()->createHiddenChild<ConsolePanel>(GUIWidget::Placement::Fill(), top_center.x, top_center.y, Core::App()->getWidth(), Core::App()->getHeight() / 4);
    // consolepanel->setActive();
    //
    // auto textbox = consolepanel->createHiddenChild<GUITextbox>(GUIWidget::Placement::Absolute());
    textbox->on("validate", [this,textbox,label]() {
      auto txt = textbox->getText();
      if (txt.size() > 0) {
        std::string ret = repl->execute_line(txt);
        textbox->setText("");
        label->setText(ret);
      }
    });
    //
    // consolepanel->on("show", [textbox](Pointer<GUIWidget> widget) {
    //   textbox->setVisible(true);
    //   textbox->setActive();
    // });
    //
    // consolepanel->on("hide", [textbox](Pointer<GUIWidget> widget) {
    //   textbox->setVisible(false);
    //   textbox->setInactive();
    // });

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
    gui->draw(batch);
    batch->end();
  }

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch2D::Ref batch;
  Scripter scripter;
  System::Ptr gui;
  Pointer<REPL> repl;
};
