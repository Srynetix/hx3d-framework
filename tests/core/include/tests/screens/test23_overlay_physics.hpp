#pragma once

#include "tests/screens/base_test_screen.hpp"

#include "hx3d/graphics/cameras/orthographic_camera.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/batches/simple_batch_2d.hpp"
#include "hx3d/gui/system.hpp"
#include "hx3d/math/vector_utils.hpp"

#include <vector>
#include <set>

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::gui;

namespace op {
class Body;
class Collider;

class CollisionResolution {
public:
  CollisionResolution();

  void computeCollision(const Pointer<Collider>& cA, const Pointer<Collider>& cB);

  Pointer<Collider> colliderA;
  Pointer<Collider> colliderB;

  glm::vec2 normal;
  std::vector<glm::vec2> contacts;
  float penetration;
  bool collision;
};

class Collider: public Transform {
public:
  enum class Type {
    Box,
    Circle
  };

  Collider(WeakPointer<Body> body);

  virtual void resolveCollision(CollisionResolution& cr, const Pointer<Collider>& co) = 0;

  float contactFriction;
  float restitution;

  bool active;
  WeakPointer<Body> body;
  Type shapeType;
};

class BoxCollider: public Collider, public std::enable_shared_from_this<BoxCollider> {
public:
  BoxCollider(WeakPointer<Body> body);

  glm::vec2 getSupport(glm::vec2 dir);

  virtual void resolveCollision(CollisionResolution& cr, const Pointer<Collider>& co) override;

  //////////

  void computeVertices();
  void computeRotation();

  float findAxisLeastPenetration(unsigned int* face, const Pointer<BoxCollider>& co);
  void findIncidentFace(std::vector<glm::vec2>& v, const Pointer<BoxCollider>& co, int refIndex);
  int clip(const glm::vec2 n, const float c, std::vector<glm::vec2>& face);

  std::vector<glm::vec2> vertices;
  std::vector<glm::vec2> normals;
  glm::mat2 rotation;
};

class CircleCollider: public Collider {
public:
  CircleCollider(WeakPointer<Body> body);
  ~CircleCollider() {}

  virtual void resolveCollision(CollisionResolution& cr, const Pointer<Collider>& co) override {}
};

class Body: public std::enable_shared_from_this<Body> {
public:
  enum class Type {
    Static,
    Dynamic,
    Kinematic
  };

  Body();

  glm::vec2 velocity;
  glm::vec2 acceleration;
  glm::vec2 force;

  float airFriction;
  bool active;
  Type type;

  Pointer<Collider> mainCollider;
  std::vector<Pointer<Collider>> colliders;

  const Pointer<Collider>& createMainCollider();
  Pointer<Collider> createCollider();
};

class Simulator {
public:
  Simulator();

  void initialize(glm::vec2 gravity, float unitScale = 1.f);
  Pointer<Body> createBody();
  void step(float delta);
  void renderDebug(const Pointer<Batch>& batch);

  std::vector<Pointer<Body>> bodies;
//  std::set<CollisionResolution> collisions;
//  std::set<CollisionResolution> inCollisions;

  glm::vec2 gravity;
  float unitScale;
};

}

class Test23: public BaseTestScreen {
public:
  Test23();

  virtual void update(float delta) override;
  virtual void render() override;

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch2D::Ref batch;

  Pointer<op::Simulator> world;
};

//////////////////
//////////////////
//////////////////
