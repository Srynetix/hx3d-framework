#include "./base_test_screen.hpp"

#include "hx3d/math/random.hpp"
#include "hx3d/graphics/fast_batch.hpp"

using namespace hx3d;

class Test6: public BaseTestScreen {
public:
  Test6():
    fShader(Core::Assets()->get<Shader>("custom2D")),
    fBatch(6000)
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    sprite.setTexture(Core::Assets()->get<Texture>("box"));

    text.setFont(Core::Assets()->get<Font>("default"));
    text.transform.position = glm::vec3(20, 20, 0.5);
    text.setCenterAlignment(false);
  }

  virtual void update(float delta) override {
    text.setContent(format("FPS: %2.2f / Draw calls: %d", 1.f/delta, fBatch.drawCalls));
  }

  virtual void render() override {
    static float angle = 0.f;
    Framebuffer::clear(Color::Black);

    unsigned int boxCountW = 50;
    unsigned int boxCountH = 25;
    float boxW = (float)Core::App()->getWidth() / boxCountW;
    float boxH = (float)Core::App()->getHeight() / boxCountH;

    Shader::use(fShader);
    fShader->setUniformMatrix4f("u_projection", camera.projection);
    fShader->setUniformMatrix4f("u_view", camera.view);
    Texture::use(sprite.getTexture());

    sprite.transform.size = {boxW, boxH, 0};

    fBatch.setShader(fShader);
    fBatch.begin();

    for (unsigned int j = 0; j < boxCountH; ++j) {
        for (unsigned int i = 0; i < boxCountW; ++i) {
            sprite.transform.position.x = boxW / 2 + i*boxW;
            sprite.transform.position.y = boxH / 2 + j*boxH;
            sprite.transform.rotation.z = glm::radians(angle);
            fBatch.draw(sprite);
        }
    }

    fBatch.end();

    batch.begin();
    batch.draw(text);
    batch.end();

    angle = math::mclamp(angle + 5, 0, 360);
  }

private:
  OrthographicCamera camera;

  Ptr<Shader> fShader;
  Batch batch;
  FastBatch fBatch;

  Sprite sprite;

  gui::Text text;
};
