/*
    Regular tween.
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

namespace hx3d {
namespace tweens {

template <class T>
Tween<T>::Tween(T& mod, const T end, const float duration, const math::Interpolation interp):
  BaseTween(), mod(&mod), end(end), duration(duration), interp(interp) {
    currentTime = 0.f;
    _firstUpdate = false;
}

template <class T>
void Tween<T>::update(const float delta) {
  if (_ended)
    return;

  if (!_firstUpdate) {
    base = *mod;
    _firstUpdate = true;
  }

  currentTime += delta;
  if (currentTime < duration) {
    const float normTime = currentTime / duration;
    *mod = math::interpolate(base, end, normTime, interp);
  } else {
    _ended = true;
  }
}

} /* tween */
} /* hx3d */
