/*
    Scene graph tests.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#include "hx3d/ecs/scene_graph.hpp"
#include <gtest/gtest.h>

namespace hx3d {

class SceneGraphTest: public testing::Test {

protected:
  SceneGraphTest() {}
  virtual ~SceneGraphTest() {}

  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(SceneGraphTest, Test) {

  SceneGraph graph;
  graph.add("///", Make<GameObject>("object"));     // Should bug
  graph.add("/coucou", Make<GameObject>(""));       // Should bug
  graph.add("/", Make<GameObject>("object"));       // Should work
  graph.add("/", Make<GameObject>("object"));       // Should work
  graph.add("/", Make<GameObject>("coucou"));       // Should work
  graph.add("/coucou", Make<GameObject>("i"));      // Should work

  graph.showEntries();
}

} /* hx3d */
