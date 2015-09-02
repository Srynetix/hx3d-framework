/*
    Base menu screen.
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

#ifndef HX3D_TEST_MENUSCREEN
#define HX3D_TEST_MENUSCREEN

#include "hx3d/core/screen.hpp"
#include "hx3d/core/input_handler.hpp"

#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/batch.hpp"

#include "hx3d/graphics/cameras/orthographic_camera.hpp"

#include <functional>
#include <vector>

class MenuScreen: public hx3d::Screen, public hx3d::InputHandler {
public:

  struct ScreenInfo {
    std::string name;
    std::function<void()> func;
  };

  MenuScreen();

  virtual void onTouchDown(glm::vec2 touchPosition, float touchPressure);

  virtual void update() override;
  virtual void render() override;

private:
  Ptr<hx3d::OrthographicCamera> camera;

  hx3d::Sprite sprite;
  hx3d::Batch batch;
  
  hx3d::gui::Text text;
  hx3d::gui::Text instructions;

  std::vector<ScreenInfo> screens;
};

#endif
