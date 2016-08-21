#include "tests/screens/test22_gui.hpp"

#include "hx3d/graphics/framebuffer.hpp"

#include "hx3d/gui/panel.hpp"
#include "hx3d/gui/label.hpp"
#include "hx3d/gui/textbox.hpp"

Test22::Test22() {
  batch->setCamera(camera);

  auto panel = Make<Panel>();
  auto label = Make<Label>();
  auto textbox = Make<TextBox>();

  label->setText("Hello");

  textbox->on("validate", [textbox, label]() {
    label->setText(textbox->getText());
  });

  system = Make<System>(Placement::Fill(panel).apply());
  panel->addChild(Placement::Relative(label, {0.75, 0.15}, {0.25, 0.15}));
  panel->addChild(Placement::Relative(textbox, {0.5, 0.85}, {0.25, 0.05}));
}

void Test22::update(float delta) {
  camera->update();

  system->update(delta);
}

void Test22::render() {
  Framebuffer::clear(Color::Black);

  batch->begin();
  system->draw(batch);
  batch->end();
}
