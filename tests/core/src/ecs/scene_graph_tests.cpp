#include "hx3d/ecs/scene_graph.hpp"
#include "hx3d/ecs/node.hpp"

#include "tests/tests.hpp"

namespace hx3d {

TEST_F(Tests, SceneGraphTests) {

  ecs::SceneGraph graph;
  auto p1 = graph.createAtRoot<ecs::Node>("object");
  auto p2 = graph.create<ecs::Node>("///", "bug");
  auto p3 = graph.create<ecs::Node>("/object", "ok");
  auto p4 = graph.create<ecs::Node>("/test", "bug");

  ASSERT_TRUE(p1 != nullptr);
  ASSERT_TRUE(p2 == nullptr);
  ASSERT_TRUE(p3 != nullptr);
  ASSERT_TRUE(p4 == nullptr);

  p1->destroy(graph);

  ASSERT_TRUE(graph.fetch<ecs::Node>("object") == nullptr);
}

} /* hx3d */
