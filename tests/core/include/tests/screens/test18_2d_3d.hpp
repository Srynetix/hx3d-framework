#include "tests/screens/base_test_screen.hpp"

#include "hx3d/hx3d.hpp"

using namespace hx3d;
using namespace hx3d::graphics;

class SGeo2: public Geometry {
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
  Test18();

  virtual void update(float delta) override;
  virtual void render() override;

private:
  OrthographicCamera::Ref camera2d;
  PerspectiveCamera::Ref camera3d;

  Mesh::Ref mesh;
  Image image;
  Sprite::Ref sprImage;
  Sprite::Ref sprite;
  tweens::TweenManager tweens;

  std::vector<int> tilesToClear;

  TimerManager timers;

  SimpleBatch::Ref batch2d;
  SimpleBatch::Ref batch3d;
};
