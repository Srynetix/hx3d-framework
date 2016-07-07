#include "./base_test_screen.hpp"

#include "hx3d/gui/panel.hpp"
#include "hx3d/gui/placement.hpp"
#include "hx3d/gui/label.hpp"
#include "hx3d/gui/system.hpp"
#include "hx3d/gui/textbox.hpp"

#include <string>

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::gui;

/*******************
  Test
********************/

class Test22: public BaseTestScreen {
public:
  Test22()
  {
    batch->setCamera(camera);

    auto panel = Make<Panel>();
    auto label = Make<Label>();
    auto textbox = Make<TextBox>();

    label->setText("Hello");

    textbox->on("validate", [textbox,label]() {
      label->setText(textbox->getText());
    });

    system = Make<System>(Placement::Fill(panel).apply());
    panel->addChild(Placement::Relative(label, {0.75, 0.15}, {0.25, 0.15}));
    panel->addChild(Placement::Relative(textbox, {0.5, 0.85}, {0.25, 0.05}));
  }

  virtual void update(float delta) override {
    camera->update();

    system->update(delta);
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    batch->begin();
    system->draw(batch);
    batch->end();
  }

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch2D::Ref batch;
  System::Ptr system;
};
