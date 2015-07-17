/*
    Default implemented screen.
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

#ifndef HX3D_CORE_SCREENADAPTER
#define HX3D_CORE_SCREENADAPTER

#include "hx3d/core/screen.hpp"

namespace hx3d {

/**
Default implemented screen.
*/
class ScreenAdapter: public Screen {

public:
  ScreenAdapter();
  virtual ~ScreenAdapter();

  virtual void show() override;
  virtual void hide() override;

  virtual void pause() override;
  virtual void resume() override;

  virtual void update() override;
  virtual void render() override;
  virtual void resize(int width, int height) override;

  virtual void dispose() override;
};

} /* hx3d */

#endif
