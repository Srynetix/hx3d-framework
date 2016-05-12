/*
    Screen transition.
    Copyright (C) 2016 Denis BOURGE

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

#ifndef HX3D_GRAPHICS_TRANSITION
#define HX3D_GRAPHICS_TRANSITION

#include "hx3d/graphics/batch.hpp"
#include "hx3d/graphics/framebuffer.hpp"

namespace hx3d {

namespace window {
  class Game;
}

namespace graphics {

/**
@brief Transition between two screens.
*/
class Transition {
public:

  /**
  @brief Create a transition

  @param game Game (Raw ptr)
  */
  Transition(window::Game* game);

  /**
  @brief Start the transition
  */
  void start();

  /**
  @brief Reset the transition
  */
  void reset();

  /**
  @brief Set the transition duration

  @param duration Duration in seconds
  */
  void setDuration(float duration);

  /**
  @brief Is the transition running

  @return True/False
  */
  bool isRunning() const;

  /**
  @brief Is the transition finished

  @return True/False
  */
  bool isFinished() const;

  /**
  @brief Update the transition

  @param delta Delta time
  */
  void update(float delta);

  /**
  @brief Render the transition

  @param batch      Batch
  @param currentFB  Current framebuffer
  @param nextFB     Next framebuffer
  */
  virtual void render(const Pointer<Batch>& batch, const Pointer<Framebuffer>& currentFB, const Pointer<Framebuffer>& nextFB) = 0;

  /**
  @brief On transition update callback

  @param delta  Delta time
  */
  virtual void onUpdate(float delta);

  /**
  @brief On transition done callback
  */
  virtual void onDone();

  /**
  @brief On transition start callback
  */
  virtual void onStart();

protected:
  /// @brief Duration in seconds
  float _duration;
  /// @brief Current time in seconds
  float _currentTime;
  /// @brief Is the transition running
  bool _running;
  /// @brief Current game
  window::Game* _game;
};

} /* graphics */
} /* hx3d */

#endif /* HX3D_GRAPHICS_TRANSITION */
