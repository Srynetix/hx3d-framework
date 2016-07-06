/*
    Audio effect display.
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

#pragma once

#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/timer.hpp"

namespace hx3d {

namespace audio {

/**
  @brief Audio effect display.

  Inherit from Sprite.

  @see Spectrum
  @see Waveform
*/
class Display: public graphics::Sprite {

public:
  /**
  @brief Create an empty display with a refresh delay of 50.

  @see initialize to construct the texture.
  */
  Display();

  /**
  @brief Create an empty display with a custom refresh delay.

  @see initialize to construct the texture.

  @param refreshDelay Refresh delay
  */
  Display(const int refreshDelay);
  virtual ~Display();

  /**
  @brief Initialize the display.

  @param width  Width
  @param height Height
  */
  void initialize(const unsigned int width, const unsigned int height);

  /**
  @brief Set the refresh delay.

  @param refreshDelay Refresh delay
  */
  void setRefreshDelay(const int refreshDelay);

  /**
  @brief Update the display.

  @param stream Stream of amplitudes (between -32767 and 32767)
  @param length Length of the stream
  @param delta Delta time
  */
  virtual void update(const short int* stream, const int length, const float delta) = 0;

  /**
  @brief Use this to execute code after initialization.

  @see Spectrum::onInitialization.
  */
  virtual void onInitialization();

  void setTexture(const Pointer<graphics::Texture>) = delete;
  void setTexture(const Pointer<graphics::Framebuffer>) = delete;

protected:
  /// @brief Drawing image
  graphics::Image _image;
  /// @brief Refresh timer
  Timer _timer;
  /// @brief Refresh delay
  int _refreshDelay;
  /// @brief Is the display initialized ?
  bool _initialized;

  /**
  @brief Draw white borders.
  */
  void drawBorders();
};

} /* audio */
} /* hx3d */
