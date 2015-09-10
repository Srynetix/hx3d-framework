/*
    Bitset.
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

#ifndef HX3D_UTILS_BITSET
#define HX3D_UTILS_BITSET

#include <cmath>
#include <vector>

namespace hx3d {

class Bitset {
public:
  Bitset();

  /**
  Set a bit to true.

  @param bit Bit
  */
  void set(unsigned int bit);

  /**
  Get the bits.
  
  @return Bits
  */
  unsigned int getBits();

private:
  unsigned int _bits;

};

} /* hx3d */

#endif
