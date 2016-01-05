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

#include "hx3d/window/screen.hpp"
#include "hx3d/window/input_handler.hpp"

#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/batch.hpp"

#include "hx3d/graphics/cameras/perspective_camera.hpp"
#include "hx3d/graphics/cameras/orthographic_camera.hpp"

#include "hx3d/graphics/viewports/fit_viewport.hpp"

#include <functional>
#include <vector>

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::window;

class MenuScreen: public Screen, public InputHandler {
public:

  struct ScreenInfo {
    std::string name;
    std::function<void()> func;
  };

  MenuScreen();

  virtual void onTouchDown(glm::vec2 touchPosition, float touchPressure) override;

  virtual void resize(int width, int height) override;
  virtual void update(float delta) override;
  virtual void render() override;

private:
  Ptr<Font> font;
  Ptr<Shader> defaultShader;
  Ptr<Shader> pixShader;

  OrthographicCamera camera;

  Sprite logoSprite;
  Sprite sprite;
  Batch batch;

  gui::Text text;
  gui::Text instructions;

  std::vector<ScreenInfo> screens;

  float buttonWidth;
  float buttonHeight;
  unsigned int buttonCount;
};

#endif
