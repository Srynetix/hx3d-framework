/*
    FFT calculation.
    Source: http://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B

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

#include "hx3d/audio/fft.hpp"

namespace hx3d {
namespace audio {

void FFT::fft(std::valarray<Complex>& vector)
{
    const size_t N = vector.size();
    if (N <= 1) return;

    // divide
    std::valarray<Complex> even = vector[std::slice(0, N/2, 2)];
    std::valarray<Complex>  odd = vector[std::slice(1, N/2, 2)];

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * math::PI * k / N) * odd[k];
        vector[k    ] = even[k] + t;
        vector[k+N/2] = even[k] - t;
    }
}

void FFT::bfft(std::valarray<Complex>& vector)
{
  // DFT
  unsigned int N = vector.size(), k = N, n;
  double thetaT = 3.14159265358979323846264338328L / N;
  Complex phiT = Complex(cos(thetaT), sin(thetaT)), T;
  while (k > 1)
  {
    n = k;
    k >>= 1;
    phiT = phiT * phiT;
    T = 1.0L;
    for (unsigned int l = 0; l < k; l++)
    {
      for (unsigned int a = l; a < N; a += n)
      {
        unsigned int b = a + k;
        Complex t = vector[a] - vector[b];
        vector[a] += vector[b];
        vector[b] = t * T;
      }
      T *= phiT;
    }
  }

  // Decimate
  unsigned int m = (unsigned int)(log(N) / log(2));
  for (unsigned int a = 0; a < N; a++)
  {
    unsigned int b = a;
    // Reverse bits
    b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
    b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
    b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
    b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
    b = ((b >> 16) | (b << 16)) >> (32 - m);
    if (b > a)
    {
      Complex t = vector[a];
      vector[a] = vector[b];
      vector[b] = t;
    }
  }

  //// Normalize (This section make it not working correctly)
  //Complex f = 1.0 / sqrt(N);
  //for (unsigned int i = 0; i < N; i++)
  //	vector[i] *= f;
}

} /* audio */
} /* hx3d */
