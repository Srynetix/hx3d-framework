#ifndef HX3D_PHYSICS_2D_WORLD
#define HX3D_PHYSICS_2D_WORLD

#include "hx3d/physics/2d/manifold.hpp"
#include "hx3d/physics/2d/collider.hpp"

#include "hx3d/physics/2d/attractors/global_attractor.hpp"
#include "hx3d/physics/2d/attractors/point_attractor.hpp"
#include "hx3d/physics/2d/attractors/zone_attractor.hpp"

#include "hx3d/graphics/batch.hpp"

namespace hx3d {
namespace physics2d {

class World {
public:
  World(const glm::vec2 globalGravity = {0, -9.81}, const unsigned int iterations = 5, const float physRatio = 30.f);

  void addAttractor(const Ptr<Attractor>& attractor);
  void addCollider(const Ptr<Collider>& collider);
  void removeCollider(const Ptr<Collider>& collider);

  void step(float dt = 1.f/60.f);
  void render(Batch& batch);

  float getPhysRatio() const;

private:
  unsigned int _iterations;
  float _physRatio;

  std::vector<Ptr<Attractor>> _attractors;
  std::vector<Ptr<Collider>> _colliders;
  std::vector<Manifold> _contacts;

  void integrateForces(const Ptr<Collider>& c, float dt);
  void integrateVelocity(const Ptr<Collider>& c, float dt);
};

}
}

#endif
