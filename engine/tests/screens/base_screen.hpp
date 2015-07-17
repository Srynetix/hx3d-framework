/*
    Base test screen.
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

#ifndef HX3D_TEST_BASESCREEN
#define HX3D_TEST_BASESCREEN

#include "hx3d/core/application.hpp"
#include "hx3d/core/game.hpp"
#include "hx3d/core/core.hpp"
#include "hx3d/core/screen_adapter.hpp"
#include "hx3d/core/events.hpp"

#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/batch.hpp"

#include "hx3d/graphics/cameras/perspective_camera.hpp"
#include "hx3d/graphics/cameras/orthographic_camera.hpp"

#include "hx3d/graphics/viewports/fit_viewport.hpp"

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/assets.hpp"

#include <gtest/gtest.h>

template <class ScreenT>
class TestGame: public hx3d::Game {
public:
  virtual void create() override {

    hx3d::Core::Assets()->create<hx3d::Texture>("box", "textures/box.jpg");

    setScreen(Make<ScreenT>());
  }
};

template <class ScreenT>
void LaunchGame() {
  hx3d::Application app(Make<TestGame<ScreenT>>(), 1280, 720, "Test", 60);
}

class ScreenTest: public testing::Test {

protected:
  ScreenTest() {}
  virtual ~ScreenTest() {}

  virtual void SetUp() {}
  virtual void TearDown() {}
};

#endif
