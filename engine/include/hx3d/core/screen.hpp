/*
    Screen management.
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

#ifndef HX3D_CORE_SCREEN
#define HX3D_CORE_SCREEN

namespace hx3d {

class Screen {

public:
  Screen();
  virtual ~Screen();

  /**
  On screen show.
  */
  virtual void show() = 0;
  /**
  On screen hide.
  */
  virtual void hide() = 0;

  /**
  On screen pause.
  */
  virtual void pause() = 0;
  /**
  On screen resume.
  */
  virtual void resume() = 0;

  /**
  On screen update.
  */
  virtual void update() = 0;
  /**
  On screen render.
  */
  virtual void render() = 0;
  /**
  On screen resize.
  @param width  New width
  @param height New height
  */
  virtual void resize(int width, int height) = 0;

  /**
  On screen disposal.
  */
  virtual void dispose() = 0;
};

} /* hx3d */

#endif
