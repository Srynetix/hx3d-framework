#include "tests/screens/test3_simple2d.hpp"

Test3::Test3(): angle(0.f)
{
  // batch->setCamera(camera);
  //
  // sprite->setTexture(Core::Assets()->get<Texture>("box"));
  //
  // text->transform.position.x = 100;
  // text->transform.position.y = 100;
  // text->transform.position.z = 0.9f;
  camera->update();

  shader = Core::Assets()->get<Shader>("base");
  Shader::use(shader);
  shader->setUniformMatrix4f("u_projection", camera->projection);
  shader->setUniformMatrix4f("u_view", camera->view);

  for (int i = 0; i < 100; ++i) {
    auto mesh = Make<Mesh2D>();
    mesh->setPosition(50 + i * 10, 50);
    mesh->setSize(9, 9);

    auto spriteGeo = Make<QuadGeometry>();
    mesh->setGeometry(spriteGeo);

    meshes.push_back(mesh);
  }
}

void Test3::update(float delta) {
  // if (Core::Events()->isKeyPressed(KeyEvent::Key::Z)) {
  //   camera->translate(glm::vec3(0, 2.f, 0));
  // }
  // else if (Core::Events()->isKeyPressed(KeyEvent::Key::S)) {
  //   camera->translate(glm::vec3(0, -2.f, 0));
  // }
  // else if (Core::Events()->isKeyPressed(KeyEvent::Key::Q)) {
  //   camera->translate(glm::vec3(-2.f, 0, 0));
  // }
  // else if (Core::Events()->isKeyPressed(KeyEvent::Key::D)) {
  //   camera->translate(glm::vec3(2.f, 0, 0));
  // }
  //
  // camera->update();
  // text->setContent(format("FPS: %2.2f", 1.f/delta));
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
    shader->setUniformMatrix4f("u_model", mesh->compute());
    mesh->draw(shader);
  }

  //
  // batch->begin();
  //
  // sprite->setTint(Color::White);
  // sprite->transform.position.z = -0.5f;
  //
  // float boxCount = 50.f;
  // float aspectRatio = (float)Core::App()->getWidth() / Core::App()->getHeight();
  // float boxSize = (float)Core::App()->getWidth() / boxCount;
  // sprite->transform.size = std::abs(std::cos(glm::radians(angle / 2))) * glm::vec3(boxSize);
  //
  // for (int j = 0; j < boxCount / aspectRatio; ++j) {
  //   sprite->transform.position.y = (j * boxSize) + boxSize / 2;
  //
  //   for (int i = 0; i < boxCount; ++i) {
  //     sprite->transform.position.x = (i * boxSize) + boxSize / 2;
  //     sprite->transform.rotation.z = glm::radians(angle * 4);
  //     batch->draw(sprite);
  //   }
  // }
  //
  // sprite->setTint(Color::Green);
  // sprite->transform.size = glm::vec3(64);
  // sprite->transform.rotation.z = glm::radians(angle * 2);
  //
  // sprite->transform.position.x = 100.f;
  // sprite->transform.position.y = 100.f;
  // sprite->transform.position.z = 0.f;
  // batch->draw(sprite);
  //
  // sprite->transform.position.x = 125.f;
  // sprite->transform.position.y = 125.f;
  // sprite->transform.position.z = 0.1f;
  // batch->draw(sprite);
  //
  // sprite->transform.position.x = 150.f;
  // sprite->transform.position.y = 150.f;
  // sprite->transform.position.z = 0.f;
  // batch->draw(sprite);
  //
  // batch->draw(text);
  //
  // batch->end();

  angle += 0.5f;
  if (angle > 360.f) {
    angle -= 360.f;
  }
}
