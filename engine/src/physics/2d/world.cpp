#include "hx3d/physics/2d/world.hpp"

#include "hx3d/graphics/sprite.hpp"

#include "hx3d/math/vector_utils.hpp"
#include "hx3d/utils/algorithm.hpp"

using namespace hx3d::graphics;

namespace hx3d {
namespace physics2d {

World::World(const glm::vec2 globalGravity, const unsigned int iterations, const float physRatio):
  _iterations(iterations), _physRatio(physRatio)
  {
    _attractors.emplace_back(Make<GlobalAttractor>(globalGravity));
  }

void World::addAttractor(const Pointer<Attractor>& attractor) {
  _attractors.push_back(attractor);
}

void World::addCollider(const Pointer<Collider>& collider) {
  _colliders.push_back(collider);
}

void World::addListener(const Pointer<CollisionListener>& listener) {
  _listeners.push_back(listener);
}

void World::removeCollider(const Pointer<Collider>& collider) {
  _colliders.erase(std::remove(_colliders.begin(), _colliders.end(), collider), _colliders.end());
}

void World::step(float dt) {

  _contacts.clear();
  _inContact.clear();

  for (unsigned int i = 0; i < _colliders.size(); ++i) {
    const Pointer<Collider>& a = _colliders[i];

    for (unsigned int j = i+1; j < _colliders.size(); ++j) {
      const Pointer<Collider>& b = _colliders[j];
      if (a->massData.invMass == 0 && b->massData.invMass == 0)
        continue;

      Manifold m(a, b);
      m.solve();

      if (m.contacts.size() > 0) {

        // Ajout dans les contacts
        _inContact.insert(m);

        if ((m.a->mask & m.b->category) || (m.b->mask & m.a->category)) {
          // Contact
        } else {
          if (m.a->category != 0 && m.b->category != 0)
            m.disabled = true;
        }

        if (prevContactExists(m)) {

          // IN
          algo::apply(_listeners, [&m](Pointer<CollisionListener>& listener) {
            listener->duringCollision(m);
          });

        } else {

          // BEGIN
          algo::apply(_listeners, [&m](Pointer<CollisionListener>& listener) {
            listener->beginCollision(m);
          });

        }

        _contacts.push_back(m);
      }
    }
  }

  // Différence entre les deux sets => END
  checkOldContacts();

  // Sauvegarde des contacts
  _inPrevContact.clear();
  algo::clone(_inContact, _inPrevContact);

  // Integrate
  for (unsigned int i = 0; i < _colliders.size(); ++i) {
    integrateForces(_colliders[i], dt);
  }

  for (unsigned int i = 0; i < _contacts.size(); ++i) {
    _contacts[i].initialize();
  }

  for (unsigned int j = 0; j < _iterations; ++j) {
    for (unsigned int i = 0; i < _contacts.size(); ++i) {
      _contacts[i].applyImpulse();
    }
  }

  for (unsigned int i = 0; i < _colliders.size(); ++i) {
    integrateVelocity(_colliders[i], dt);
  }

  for (unsigned int i = 0; i < _contacts.size(); ++i) {
    _contacts[i].positionalCorrection();
  }

  for (unsigned int i = 0; i < _colliders.size(); ++i) {
    const Pointer<Collider>& c = _colliders[i];
    c->force = {0, 0};
    c->gravityForce = {0.f, 0.f};
    c->torque = 0;
  }
}

void World::render(const Pointer<graphics::Batch>& batch) {

  for (unsigned int i = 0; i < _attractors.size(); ++i) {
    const Pointer<Attractor>& attractor = _attractors[i];

    if (attractor->type == Attractor::Type::Zone) {
      const Pointer<ZoneAttractor>& zone = std::dynamic_pointer_cast<ZoneAttractor>(attractor);
      Pointer<Sprite> sprite = Make<Sprite>();
      sprite->setTexture(Texture::Blank);
      sprite->transform.position.x = zone->position.x * _physRatio;
      sprite->transform.position.y = zone->position.y * _physRatio;
      sprite->transform.position.z = -0.25f;
      sprite->transform.size.x = zone->width * _physRatio;
      sprite->transform.size.y = zone->height * _physRatio;

      sprite->setTint(Color(240, 20, 201));
      batch->draw(sprite);
    }

    else if (attractor->type == Attractor::Type::Point) {
      const Pointer<PointAttractor>& point = std::dynamic_pointer_cast<PointAttractor>(attractor);
      Pointer<Sprite> sprite = Make<Sprite>();
      sprite->setTexture(Texture::Blank);
      sprite->transform.position.x = point->position.x * _physRatio;
      sprite->transform.position.y = point->position.y * _physRatio;
      sprite->transform.position.z = -0.25f;
      sprite->transform.size.x = point->radius * 2 * _physRatio;
      sprite->transform.size.y = point->radius * 2 * _physRatio;

      sprite->setTint(Color(20, 240, 201));
      batch->draw(sprite);
    }
  }

  for (unsigned int i = 0; i < _colliders.size(); ++i) {
    const Pointer<Collider>& c = _colliders[i];

    Pointer<Sprite> sprite = Make<Sprite>();
    sprite->setTexture(Texture::Blank);
    sprite->transform.position.x = c->position.x * _physRatio;
    sprite->transform.position.y = c->position.y * _physRatio;

    if (c->shape == Collider::Shape::Polygon) {
      const Pointer<Polygon>& b = std::dynamic_pointer_cast<Polygon>(c);
      if (b->box) {
        float w = b->vertices[1].x * 2;
        float h = b->vertices[2].y * 2;
        sprite->transform.size.x = w * _physRatio;
        sprite->transform.size.y = h * _physRatio;
      }
    }

    else if (c->shape == Collider::Shape::Circle) {
      const Pointer<Circle>& b = std::dynamic_pointer_cast<Circle>(c);
      sprite->transform.size.x = (b->radius / 2) * _physRatio;
      sprite->transform.size.y = (b->radius / 2) * _physRatio;
    }

    sprite->transform.rotation.z = c->orientation;

    if (c->type == Collider::Type::Static)
      sprite->setTint(Color::Blue);
    else
      sprite->setTint(Color::Red);

    batch->draw(sprite);
  }

  for (unsigned int i = 0; i < _contacts.size(); ++i) {
    const Manifold& m = _contacts[i];

    for (unsigned int j = 0; j < m.contacts.size(); ++j) {
      const glm::vec2& contact = m.contacts[j];

      Pointer<Sprite> sprite = Make<Sprite>();
      sprite->setTexture(Texture::Blank);
      sprite->setTint(Color::Green);
      sprite->transform.position.x = contact.x * _physRatio;
      sprite->transform.position.y = contact.y * _physRatio;
      sprite->transform.position.z = 0.5f;
      sprite->transform.size.x = 5;
      sprite->transform.size.y = 5;

      batch->draw(sprite);
    }
  }

  for (unsigned int i = 0; i < _contacts.size(); ++i) {
    const Manifold& m = _contacts[i];

    for (unsigned int j = 0; j < m.contacts.size(); ++j) {
      const glm::vec2& contact = m.contacts[j];

      Pointer<Sprite> sprite = Make<Sprite>();
      sprite->setTexture(Texture::Blank);
      sprite->setTint(Color(255, 0, 255));
      sprite->transform.size.x = 3;
      sprite->transform.size.y = 20;
      sprite->transform.position.x = contact.x * _physRatio;
      sprite->transform.position.y = contact.y * _physRatio;
      sprite->transform.position.z = 0.75f;
      sprite->transform.rotation.z = math::angleBetweenVecs(glm::vec2(0, 1), m.normal);

      batch->draw(sprite);
    }
  }
}

float World::getPhysRatio() const {
  return _physRatio;
}

const Pointer<GlobalAttractor> World::getGlobalGravity() {
  return std::dynamic_pointer_cast<GlobalAttractor>(_attractors[0]);
}

CollisionMatrix& World::getCollisionMatrix() {
  return _collisionMatrix;
}

///////////////

void World::integrateForces(const Pointer<Collider>& c, float dt) {
  if (c->massData.invMass == 0.f)
    return;

  for (auto attractor: _attractors) {
    Attractor::applyForce(c, attractor, dt);
  }

  // c->velocity += c->gravityForce;
  c->velocity += ((c->force * c->massData.invMass) + (c->gravityForce * 2.f)) * (dt / 2.f);
  if (!c->fixedRotation) {
    c->angularVelocity += c->torque * c->massData.invInertia * (dt / 2.f);
  }
}

void World::integrateVelocity(const Pointer<Collider>& c, float dt) {
  if (c->type != Collider::Type::Kinematic && c->massData.invMass == 0.f)
    return;

  c->position += c->velocity * dt;

  // Calcul de l'angle
  //
  // glm::vec2 nP = glm::vec2(0, -1);
  // glm::vec2 nG = glm::normalize(c->gravityForce);
  // float angle = 0.f;
  // float a = glm::dot(nP, nG);
  //
  // if (nG.x < 0) {
  //   angle = -std::acos(a);
  // } else {
  //   angle = std::acos(a);
  // }
  //
  // c->setOrientation(angle);

  if (!c->fixedRotation) {
    c->orientation += c->angularVelocity * dt;
    c->setOrientation(c->orientation);
  }

  integrateForces(c, dt);
}

bool World::prevContactExists(Manifold& m) {
  bool result = false;
  for (auto& ma: _inPrevContact) {
    if (ma.a == m.a && ma.b == m.b)
    {
      result = true;
      break;
    }
  }

  return result;
}

void World::checkOldContacts() {
  std::set<Manifold> diffSet;
  for (auto& manif: _inPrevContact) {
    bool inside = false;
    for (auto& curr: _contacts) {
      if (curr.a == manif.a && curr.b == manif.b) {
        inside = true;
      }
    }

    if (!inside) {
      diffSet.insert(manif);
    }
  }

  algo::apply(diffSet, [this](Manifold manif) {
    algo::apply(_listeners, [&manif](Pointer<CollisionListener> listener) {
      listener->endCollision(manif);
    });
  });
}

} /* physics2d */
} /* hx3d */
