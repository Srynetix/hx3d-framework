#include "./base_test_screen.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/window/game.hpp"
#include "hx3d/utils/algorithm.hpp"
#include "hx3d/tweens.hpp"

#include "hx3d/physics/2d/world.hpp"
#include "hx3d/physics/2d/collider.hpp"

using namespace hx3d;

class SGeo2: public geom::Geometry {
public:
  SGeo2(unsigned int tris) {
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

class Test18: public BaseTestScreen {
public:
  Test18():
    camera3d(0.1f, 3500.f)
  {
    glm::vec2 worldSize = Core::CurrentGame()->getSize();

    constexpr int tileSize = 64;
    tilesToClear = algo::range(0, (int)(std::ceil(worldSize.x / tileSize) * std::ceil(worldSize.y / tileSize)));

    camera3d.translate(glm::vec3(0.f, 0.f, -1000.f));
    camera3d.rotate(180.f, glm::vec3(0, 1, 0));
    camera3d.update();

    batch2d.setShader(Core::Assets()->get<Shader>("base"));
    batch2d.setCamera(camera2d);

    batch3d.setShader(Core::Assets()->get<Shader>("base"));
    batch3d.setCamera(camera3d);

    mesh.setGeometry(Make<SGeo2>(16000));
    mesh.transform.size = glm::vec3(2);
    mesh.transform.position = glm::vec3(0);

    image.create(Core::CurrentGame()->getSize().x, Core::CurrentGame()->getSize().y);
    image.setRect(0, 0, Core::CurrentGame()->getSize().x-1, Core::CurrentGame()->getSize().y-1, Color::White);
    image.buildTexture();

    sprite.setTexture(Core::Assets()->get<Texture>("logo"));
    sprite.transform.position.x = Core::CurrentGame()->getSize().x / 2;
    sprite.transform.position.y = Core::CurrentGame()->getSize().y / 2;
    sprite.transform.position.z = 0.1f;

    sprImage.setTexture(image.getTexture());
    sprImage.transform.position.x = Core::CurrentGame()->getSize().x / 2;
    sprImage.transform.position.y = Core::CurrentGame()->getSize().y / 2;
    sprImage.transform.position.z = 0.5f;

    auto seq = Make<tweens::Sequence>(true);
    seq->addTween(sprite.transform.rotation.z, 2 * 3.14f, 5, math::Interpolation::InOutElastic);
    tweens.add(seq);

    timers.createNamedTimer("carr", 10, [this, worldSize, tileSize](){

      if (tilesToClear.empty())
        return;

      int i = math::random(0, tilesToClear.size() - 1);
      int elem = tilesToClear[i];
      tilesToClear.erase(tilesToClear.begin() + i);

      int x = elem % (int)(std::floor(worldSize.x / tileSize));
      int y = elem / (int)(std::floor(worldSize.x / tileSize));

      image.setRect(x * tileSize, y * tileSize, tileSize, tileSize, Color(0, 255, 255, 0));
      image.updateTextureZone(x * tileSize, y * tileSize, tileSize, tileSize);

      timers.resetNamedTimer("carr");
    });
  }

  virtual void update(float delta) override {
    camera3d.rotateAround(glm::vec3(0, 0, 0), 1.f, glm::vec3(0, 1, 0));
    camera3d.update();

    tweens.update(delta);
    timers.update(delta);
  }

  virtual void render() override {
    Framebuffer::clear(Color(0, 0, 0));

    batch3d.begin();
    batch3d.draw(mesh);
    batch3d.end();

    batch2d.begin();
    batch2d.draw(sprite);
    batch2d.draw(sprImage);
    batch2d.end();
  }

private:
  OrthographicCamera camera2d;
  PerspectiveCamera camera3d;

  Mesh mesh;
  Image image;
  Sprite sprImage;
  Sprite sprite;
  tweens::TweenManager tweens;

  std::vector<int> tilesToClear;

  TimerManager timers;

  Batch batch2d;
  Batch batch3d;
};
