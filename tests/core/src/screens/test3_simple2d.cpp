#include "tests/screens/test3_simple2d.hpp"

int rand();

Test3::Test3(): angle(0.f)
{
  camera->update();

  shader = Core::Assets()->get<Shader>("fast2D");
  Shader::use(shader);
  shader->setUniformMatrix4f("u_projection", camera->projection);
  shader->setUniformMatrix4f("u_view", camera->view);

  for (int i = 0; i < 100; ++i) {
    auto mesh = Make<Mesh2D>();
    mesh->setPosition(50 + i * 10, 50);
    mesh->setSize(9, 9);

    auto spriteGeo = Make<QuadGeometry>();
    mesh->setGeometry(spriteGeo);
    mesh->setGeometryDrawer(Make<FastSpriteDrawer>());

    meshes.push_back(mesh);
  }
}

void Test3::update(float delta) {
}

void Test3::render() {
  Framebuffer::clear(Color::Black);

  for (auto& mesh: meshes) {
    auto Log = Logger::getLogger("tests");

    if (rand() % 5 == 2) {
      mesh->setPosition(rand() % (50 + Core::App()->getWidth() - 50), rand() % (50 + Core::App()->getHeight() - 50));

      mesh->setSize(rand() % 50, rand() % 50);
    }

    Shader::use(shader);
    Texture::use(Texture::Blank);
    mesh->draw(shader);
  }

  angle += 0.5f;
  if (angle > 360.f) {
    angle -= 360.f;
  }
}
