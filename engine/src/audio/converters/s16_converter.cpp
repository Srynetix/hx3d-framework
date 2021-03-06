/*
    Audio Converter: Signed Short.
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

#include "hx3d/audio/converters/s16_converter.hpp"

namespace hx3d {
namespace audio {

S16Converter::S16Converter(): Effect() {}
S16Converter::~S16Converter() {}

void S16Converter::onFunction(const int channel, const void* stream, const int length) {
  if (!_stream)
    _stream = new short[length/2];
  _length = length/2;

  short* my_stream = (short*)_stream;
  char* str = (char*)stream;

  for (int i = 0; i < length; i += 2) {
    char a = str[i+1];
    char b = str[i];
    unsigned char ua = a < 0 ? 127 - a : a;
    unsigned char ub = b < 0 ? 127 - b : b;
    unsigned short us = (ua << 8 | ub);
    short s = us > 32767 ? -(us - 32767) : us;

    my_stream[i/2] = s;
  }

  _processed = true;
}

void S16Converter::onDone(const int channel)
{}

short* S16Converter::getS16Stream() {
  return (short*)_stream;
}

} /* audio */
} /* hx3d */
