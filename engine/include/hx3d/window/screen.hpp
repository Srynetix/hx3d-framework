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

#ifndef HX3D_WINDOW_SCREEN
#define HX3D_WINDOW_SCREEN

namespace hx3d {

class Screen {

public:
  Screen();
  virtual ~Screen();

  /**
  On screen show.
  */
  virtual void show();
  /**
  On screen hide.
  */
  virtual void hide();

  /**
  On screen pause.
  */
  virtual void pause();
  /**
  On screen resume.
  */
  virtual void resume();

  /**
  On screen update.

  @param delta Delta time
  */
  virtual void update(float delta);
  /**
  On screen render.
  */
  virtual void render();
  /**
  On screen resize.

  @param width  New width
  @param height New height
  */
  virtual void resize(int width, int height);

  /**
  On screen disposal.
  */
  virtual void dispose();
};

} /* hx3d */

#endif /* HX3D_WINDOW_SCREEN */
