/*
    FFT calculation.
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

#ifndef HX3D_AUDIO_FFT
#define HX3D_AUDIO_FFT

#include "hx3d/math/constants.hpp"

#include <valarray>

namespace hx3d {
namespace audio {

class FFT {
public:

  // Cooley–Tukey FFT (in-place, divide-and-conquer)
  // Higher memory requirements and redundancy although more intuitive
  static void fft(std::valarray<Complex>& vector);

  // Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
  // Better optimized but less intuitive
  static void bfft(std::valarray<Complex>& vector);
};

} /* audio */
} /* hx3d */

#endif
