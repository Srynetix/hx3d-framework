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
  World(glm::vec2 globalGravity = {0, -9.81}, unsigned int iterations = 5, float dt = 1.f/60.f);

  void addAttractor(const Ptr<Attractor>& attractor);
  void addCollider(const Ptr<Collider>& collider);
  void removeCollider(const Ptr<Collider>& collider);

  void step();
  void render(Batch& batch, float unitCoef = 30.f);

private:
  unsigned int _iterations;
  float _deltaTime;

  std::vector<Ptr<Attractor>> _attractors;
  std::vector<Ptr<Collider>> _colliders;
  std::vector<Manifold> _contacts;

  void integrateForces(const Ptr<Collider>& c, float dt);
  void integrateVelocity(const Ptr<Collider>& c, float dt);
};

}
}

#endif
