#include "./base_test_screen.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/geometries/cube_geometry.hpp"

#include "hx3d/math/random.hpp"

using namespace hx3d;

class SGeo: public Geometry {
public:
  SGeo(unsigned int tris) {
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<GLushort> indices;

    positions.resize(tris * 3 * 3);
    colors.resize(tris * 3 * 4);
    indices.resize(tris * 3);

    unsigned int n = 800;
    unsigned int n2 = n / 2;
    unsigned int d = 12;
    unsigned int d2 = d / 2;

    unsigned int i = 0, i_color = 0;
    bool ok_p = false, ok_c = false;

    while (!ok_p || !ok_c) {
      float x = math::randfloat() * n - n2;
      float y = math::randfloat() * n - n2;
      float z = math::randfloat() * n - n2;

      float ax = x + math::randfloat() * d - d2;
      float ay = y + math::randfloat() * d - d2;
      float az = z + math::randfloat() * d - d2;

      float bx = x + math::randfloat() * d - d2;
      float by = y + math::randfloat() * d - d2;
      float bz = z + math::randfloat() * d - d2;

      float cx = x + math::randfloat() * d - d2;
      float cy = y + math::randfloat() * d - d2;
      float cz = z + math::randfloat() * d - d2;

      float vx = ( x / n ) + 0.5;
      float vy = ( y / n ) + 0.5;
      float vz = ( z / n ) + 0.5;

      if (i < tris * 3 * 3) {
        positions[ i ]     = ax;
        positions[ i + 1 ] = ay;
        positions[ i + 2 ] = az;

        positions[ i + 3 ] = bx;
        positions[ i + 4 ] = by;
        positions[ i + 5 ] = bz;

        positions[ i + 6 ] = cx;
        positions[ i + 7 ] = cy;
        positions[ i + 8 ] = cz;
      } else {
        ok_p = true;
      }

      if (i_color < tris * 3 * 4) {
        colors[ i_color ]     = vx;
        colors[ i_color + 1 ] = vy;
        colors[ i_color + 2 ] = vz;
        colors[ i_color + 3 ] = 1.f;

        colors[ i_color + 4 ] = vx;
        colors[ i_color + 5 ] = vy;
        colors[ i_color + 6 ] = vz;
        colors[ i_color + 7 ] = 1.f;

        colors[ i_color + 8 ] = vx;
        colors[ i_color + 9 ] = vy;
        colors[ i_color + 10 ] = vz;
        colors[ i_color + 11 ] = 1.f;
      } else {
        ok_c = true;
      }

      i += 9;
      i_color += 12;
    }

    for (unsigned int i = 0; i < tris*3; i += 3) {
      indices[i] = i;
      indices[i+1] = i+1;
      indices[i+2] = i+2;
    }

    setAttribute("Position", positions);
    setAttribute("Color", colors);
    setIndices(indices);

    uploadAll();
  }
};

struct RollMovement: public InputHandler {

  float movement_x;
  bool roll_on;

  RollMovement() {
    movement_x = 0;
    roll_on = false;
  }

  virtual void onTouchDown(glm::vec2 touchPosition, float touchPressure) override {
    movement_x = 0;
    roll_on = true;
  }

  virtual void onTouchUp(glm::vec2 touchPosition, float touchPressure) override {
    roll_on = false;
  }

  virtual void onTouchMotion(glm::vec2 touchPosition, glm::vec2 touchMovement, float touchPressure) override {
    if (roll_on) {
      movement_x = touchMovement.x;
    }
  }

  void updateCamera(float delta, const Pointer<Camera>& camera) {
    camera->rotateAround({0, 0, 0}, glm::degrees(movement_x / 250.f), {0, 1, 0});
    camera->update();

    float dt = 0.5f;
    movement_x += movement_x > 0 ? -dt : dt;

    if (movement_x >= -dt && movement_x <= dt)
      movement_x = 0;
  }
};

class Test14: public BaseTestScreen {
public:
  Test14():
    camera(0.1f, 3500.f)
  {
    camera->translate(glm::vec3(0.f, 0.f, -1000.f));
    camera->rotate(180.f, glm::vec3(0, 1, 0));
    camera->update();

    mesh->setGeometry(Make<SGeo>(16000));
    mesh->transform.size = glm::vec3(2);
    mesh->transform.position = glm::vec3(0);

    batch->setCamera(camera);

    fps->setContent("FPS: ");
    fps->transform.position.x = -2000;
    fps->transform.position.y = 0;
    fps->transform.position.z = 0.5f;
    fps->transform.size = glm::vec3(1);
  }

  virtual void show() override {
    BaseTestScreen::show();
    Core::Events()->registerHandler(&ballMovement);
  }

  virtual void hide() override {
    BaseTestScreen::hide();
    Core::Events()->unregisterHandler(&ballMovement);
  }

  virtual void onTouchDown(glm::vec2 touchPosition, float touchPressure) override {
    ballMovement.onTouchDown(touchPosition, touchPressure);
  }

  virtual void onTouchUp(glm::vec2 touchPosition, float touchPressure) override {
    ballMovement.onTouchUp(touchPosition, touchPressure);
  }

  virtual void onTouchMotion(glm::vec2 touchPosition, glm::vec2 touchMovement, float touchPressure) override {
    ballMovement.onTouchMotion(touchPosition, touchMovement, touchPressure);
  }

  virtual void update(float delta) override {
    ballMovement.updateCamera(delta, camera);
    fps->setContent(format("FPS: %2.2f", 1.f/delta));
  }

  virtual void render() override {
    Framebuffer::clear(Color(0, 0, 0));

    batch->begin();
    batch->draw(mesh);
    batch->draw(fps);
    batch->end();
  }

private:
  RollMovement ballMovement;
  PerspectiveCamera::Ref camera;
  Mesh::Ref mesh;

  gui::Text::Ref fps;

  SimpleBatch::Ref batch;
};
