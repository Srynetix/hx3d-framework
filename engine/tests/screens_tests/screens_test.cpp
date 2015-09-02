/*
    Screens test.
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

#ifndef HX3D_TEST_SCREENSTEST
#define HX3D_TEST_SCREENSTEST

#include "hx3d/core/application.hpp"
#include "hx3d/core/game.hpp"
#include "hx3d/core/core.hpp"

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/assets.hpp"

#include "./menu_screen.hpp"

#include <gtest/gtest.h>

class TestGame: public hx3d::Game {
public:
  virtual void create() override {
    hx3d::Core::Assets()->create<hx3d::Texture>("box", "textures/box.jpg");
    hx3d::Core::Events()->emulateTouchWithMouse(true);

    setScreen(Make<MenuScreen>());
  }
};

class ScreensTest: public testing::Test {

protected:
  ScreensTest() {}
  virtual ~ScreensTest() {}

  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(ScreensTest, Screens) {
  hx3d::ApplicationConfig config;
  config.title = "Tests";

  hx3d::Application app(Make<TestGame>(), config);
}

#endif
