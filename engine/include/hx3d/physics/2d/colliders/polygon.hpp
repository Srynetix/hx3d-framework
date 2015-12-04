#ifndef HX3D_PHYSICS_2D_COLLIDERS_POLYGON
#define HX3D_PHYSICS_2D_COLLIDERS_POLYGON

#include "hx3d/physics/2d/collider.hpp"

#include <vector>

namespace hx3d {
namespace physics2d {
namespace colliders {

struct Polygon: public Collider {
  unsigned int vertexCount;
  std::vector<glm::vec2> vertices;
  std::vector<glm::vec2> normals;
  glm::mat2 u;
  bool box;

  Polygon(const Type colliderType = Type::Dynamic);
  void setPoints(const std::vector<glm::vec2>& points);

  glm::vec2 getSupport(glm::vec2 dir);
  void setAsBox(const float width, const float height);

  virtual void setOrientation(float angle) override;
  virtual void computeMass(float density) override;
};

} /* physics2d */
} /* colliders */
} /* hx3d */

#endif
