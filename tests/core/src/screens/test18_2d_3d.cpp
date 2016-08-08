#include "tests/screens/test18_2d_3d.hpp"

Test18::Test18():
  camera3d(0.1f, 3500.f)
{
  glm::vec2 worldSize = Core::CurrentGame()->getSize();

  constexpr int tileSize = 8;
  constexpr int qty = 300;
  tilesToClear = algo::range(0, (int)(std::ceil(worldSize.x / (float)tileSize) * std::ceil(worldSize.y / (float)tileSize)));

  camera3d->translate(glm::vec3(0.f, 0.f, -1000.f));
  camera3d->rotate(180.f, glm::vec3(0, 1, 0));
  camera3d->update();

  batch2d->setCamera(camera2d);
  batch3d->setCamera(camera3d);

  mesh->setGeometry(Make<SGeo2>(16000));
  mesh->transform.size = glm::vec3(2);
  mesh->transform.position = glm::vec3(0);

  image.create(Core::CurrentGame()->getSize().x, Core::CurrentGame()->getSize().y);
  image.setRect(0, 0, Core::CurrentGame()->getSize().x-1, Core::CurrentGame()->getSize().y-1, Color::White);
  image.buildTexture();

  sprite->setTexture(Core::Assets()->get<Texture>("logo"));
  sprite->transform.scale.x = 0.5f;
  sprite->transform.scale.y = 0.5f;
  sprite->transform.position.x = Core::CurrentGame()->getSize().x / 2;
  sprite->transform.position.y = Core::CurrentGame()->getSize().y / 2;
  sprite->transform.position.z = 0.1f;

  sprImage->setTexture(image.getTexture());
  sprImage->transform.position.x = Core::CurrentGame()->getSize().x / 2;
  sprImage->transform.position.y = Core::CurrentGame()->getSize().y / 2;
  sprImage->transform.position.z = 0.5f;

  auto seq = Make<tweens::Sequence>(true);
  seq->addTween(sprite->transform.rotation.z, 2 * 3.14f, 5, math::Interpolation::InOutElastic);
  tweens.add(seq);

  timers.createNamedTimer("carr", 1, [this, worldSize, tileSize](){

    for (int k = 0; k < qty; ++k) {
      if (tilesToClear.empty())
        return;

      auto i = math::random(0UL, tilesToClear.size() - 1);
      int elem = tilesToClear[i];
      tilesToClear.erase(tilesToClear.begin() + i);

      unsigned int x = elem % (unsigned int)(std::floor(worldSize.x / (float)tileSize));
      unsigned int y = (elem / (unsigned int)(std::floor(worldSize.x / (float)tileSize)));

      image.setRect(x * tileSize, y * tileSize, tileSize, tileSize, Color(0, 255, 255, 0));
      image.updateTextureZone(x * tileSize, y * tileSize, tileSize, tileSize);
    }

    timers.resetNamedTimer("carr");
  });
}

void Test18::update(float delta) {
  camera3d->rotateAround(glm::vec3(0, 0, 0), 1.f, glm::vec3(0, 1, 0));
  camera3d->update();

  tweens.update(delta);
  timers.update(delta);
}

void Test18::render() {
  Framebuffer::clear(Color(0, 0, 0));

  batch3d->begin();
  batch3d->draw(mesh);
  batch3d->end();

  batch2d->begin();
  batch2d->draw(sprite);
  batch2d->draw(sprImage);
  batch2d->end();
}
