#include "tests/screens/test3_simple2d.hpp"

Test3::Test3(): angle(0.f)
{
  camera->update();

  shader = Core::Assets()->get<Shader>("fast2D");

  Shader::use(shader);
  shader->setUniformMatrix4f("u_projection", camera->projection);
  shader->setUniformMatrix4f("u_view", camera->view);

  float size = 20;
  int qtyX = (int)std::floor(Core::App()->getWidth() / size);
  int qtyY = (int)std::floor(Core::App()->getHeight() / size);

  spBatch = Make<SpriteBatch>(qtyX*qtyY+1);
  spBatch->setShader(shader);

  auto Log = Logger::getLogger("tests");
  Log.Info("Count: %d", qtyX*qtyY);

  for (int j = 0; j < qtyY; ++j) {
    for (int i = 0; i < qtyX; ++i) {

      auto mesh = Make<Mesh>();
      mesh->setGeometry(Make<SpriteGeometry>());

      mesh->setPosition(size / 2 + i * (size*1.1f), size / 2 + j * (size*1.1f));
      mesh->setSize(size, size);
      mesh->setTint(Color::White);

      meshes.push_back(mesh);

      spBatch->draw(mesh);
    }
  }

  spBatch->setTexture(Core::Assets()->get<Texture>("box"));
}

void Test3::update(float delta) {

  for (int i = 0; i < 2; ++i) {
    unsigned int id = math::random(0UL, meshes.size() - 1UL);

    auto& mesh = meshes[id];
    mesh->rotate(glm::radians(math::random(-10.f, 10.f)));

    auto col = Color(math::random(0, 255), math::random(0, 255), math::random(0, 255));
    mesh->setTint(col);

    spBatch->draw(mesh);
  }
}

void Test3::render() {
  Framebuffer::clear(Color::Black);

  spBatch->render();
}
