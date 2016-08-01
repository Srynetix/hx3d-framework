#include "tests/screens/test3_simple2d.hpp"

Test3::Test3(): angle(0.f)
{
  camera->update();

  shader = Core::Assets()->get<Shader>("base");
  Shader::use(shader);
  shader->setUniformMatrix4f("u_projection", camera->projection);
  shader->setUniformMatrix4f("u_view", camera->view);

  auto aW = Core::App()->getWidth();
  auto aH = Core::App()->getHeight();

  auto qtyW = 50;
  auto qtyH = 50;

  auto qW = (float)aW / (float)qtyW;
  auto qH = (float)aH / (float)qtyH;

  for (int j = 0; j < qtyH; ++j) {
    for (int i = 0; i < qtyW; ++i) {
      auto mesh = Make<Mesh2D>();
      mesh->setPosition(i * qW + qW / 2, j * qH + qH / 2);
      mesh->setSize(qW - 5, qH - 5);

      auto spriteGeo = Make<QuadGeometry>();
      spriteGeo->setAttribute("Color", std::vector<float> {
        0, 1, 1, 1,
        0, 1, 0, 1,
        1, 1, 0, 1,
        1, 0, 1, 1
      });
      spriteGeo->getAttribute("Color").upload();

      mesh->setGeometry(spriteGeo);
      meshes.push_back(mesh);
    }
  }
}

void Test3::update(float delta) {
}

void Test3::render() {
  Framebuffer::clear(Color::Black);

  for (auto& mesh: meshes) {
    mesh->setRotation(rand() % 360);

    Shader::use(shader);
    Texture::use(Texture::Blank);
    shader->setUniformMatrix4f("u_model", mesh->compute());
    mesh->draw(shader);
  }

  angle += 0.5f;
  if (angle > 360.f) {
    angle -= 360.f;
  }
}
