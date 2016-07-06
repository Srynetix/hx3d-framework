/*
    Audio effect.
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

namespace hx3d {
namespace audio {

/**
@brief Audio effect manipulation

You can inherit the effect to use a custom function/filter on a channel.
*/
class Effect {
public:
  Effect();
  virtual ~Effect();

  /**
  @brief Audio effect function.

  @see AudioDevice#registerEffect

  @param channel Audio channel
  @param stream  Audio stream
  @param length  Sample length
  */
  virtual void onFunction(const int channel, const void* stream, const int length);

  /**
  @brief Audio effect done function.

  @see AudioDevice#registerEffect

  @param channel Audio channel
  */
  virtual void onDone(const int channel);

  /**
  @brief Get the audio channel related to the effect.

  @return Audio channel
  */
  int getChannel();

  /**
  @brief Get the audio stream.

  @return Audio stream
  */
  void* getStream();

  /**
  @brief Get the sample size.

  @return Sample size
  */
  int getSampleSize();

  /**
  @brief Test if the effect has started.
  */
  bool hasProcessed();

protected:

  /// @brief Has the effect started ?
  bool _processed;

  /// @brief Audio channel
  int _channel;

  /// @brief Sound stream
  void* _stream;

  /// @brief Sound length
  int _length;
};

} /* audio */
} /* hx3d */
