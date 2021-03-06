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

#include "hx3d/audio/effect.hpp"

namespace hx3d {
namespace audio {

Effect::Effect(): _processed(false), _channel(-1), _stream(nullptr), _length(0) {}
Effect::~Effect() {}

void Effect::onFunction(const int channel, const void* stream, const int length) {}
void Effect::onDone(const int channel) {}

int Effect::getChannel() {
  return _channel;
}
void* Effect::getStream() {
  return _stream;
}
int Effect::getSampleSize() {
  return _length;
}
bool Effect::hasProcessed() {
  return _processed;
}


} /* audio */
} /* hx3d */
