/*
    Test screen one.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#include "./base_screen.hpp"

using namespace hx3d;

class ScreenThree: public ScreenAdapter {
public:
  ScreenThree():
    shader(Core::Assets()->get<Shader>("base")),
    camera(Make<OrthographicCamera>(Core::App()->getWidth(), Core::App()->getHeight())),
    texture(Core::Assets()->get<Texture>("box")),
    sprite(texture),
    angle(0.f)
  {
    batch.setCamera(camera);
    batch.setShader(shader);
  }

  void update() {
    if (Core::Events()->isKeyPressed(KeyEvent::Key::Escape)) {
      Core::CurrentGame()->stop();
    }

    if (Core::Events()->isKeyPressed(KeyEvent::Key::Z)) {
      camera->translate(glm::vec3(0, 2.f, 0));
    }
    else if (Core::Events()->isKeyPressed(KeyEvent::Key::S)) {
      camera->translate(glm::vec3(0, -2.f, 0));
    }
    else if (Core::Events()->isKeyPressed(KeyEvent::Key::Q)) {
      camera->translate(glm::vec3(-2.f, 0, 0));
    }
    else if (Core::Events()->isKeyPressed(KeyEvent::Key::D)) {
      camera->translate(glm::vec3(2.f, 0, 0));
    }
  }

  void render() {

      Camera::clear(Color(0, 0, 0));

      batch.begin();

      sprite.setTint(Color(255, 255, 255));
      sprite.transform.position.z = -0.5f;

      float boxCount = 20.f;
      float aspectRatio = (float)Core::App()->getWidth() / Core::App()->getHeight();
      float boxSize = (float)Core::App()->getWidth() / boxCount;
      sprite.transform.scale = std::abs(std::cos(glm::radians(angle / 2))) * glm::vec3(boxSize);

      for (int j = 0; j < boxCount / aspectRatio; ++j) {
        sprite.transform.position.y = (j * boxSize) + boxSize / 2;

        for (int i = 0; i < boxCount; ++i) {
          sprite.transform.position.x = (i * boxSize) + boxSize / 2;
          sprite.transform.rotation.z = glm::radians(angle * 4);
          batch.draw(sprite);
        }
      }

      sprite.setTint(Color(0, 255, 0));
      sprite.transform.scale = glm::vec3(64);
      sprite.transform.rotation.z = glm::radians(angle * 2);

      sprite.transform.position.x = 100.f;
      sprite.transform.position.y = 100.f;
      sprite.transform.position.z = 0.f;
      batch.draw(sprite);

      sprite.transform.position.x = 125.f;
      sprite.transform.position.y = 125.f;
      sprite.transform.position.z = 0.1f;
      batch.draw(sprite);

      sprite.transform.position.x = 150.f;
      sprite.transform.position.y = 150.f;
      sprite.transform.position.z = 0.f;
      batch.draw(sprite);

      batch.end();

      angle += 0.5f;
      if (angle > 360.f) {
        angle -= 360.f;
      }
  }

private:
  Ptr<hx3d::Shader> shader;
  Ptr<hx3d::OrthographicCamera> camera;
  Ptr<hx3d::Texture> texture;

  hx3d::Batch batch;
  hx3d::Sprite sprite;

  float angle;
};

TEST_F(ScreenTest, ScreenThree) {
//  LaunchGame<ScreenThree>();
}
