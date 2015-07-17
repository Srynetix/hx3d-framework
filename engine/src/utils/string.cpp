/*
    String helper functions.
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

#include "hx3d/utils/string.hpp"

namespace hx3d {

std::string format(const std::string fmt, ...) {

    int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
    std::string str;
    va_list ap;
    while (1) {     // Maximum two passes on a POSIX system...
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {  // Everything worked
            str.resize(n);
            return str;
        }
        if (n > -1)  // Needed size returned
            size = n + 1;   // For null char
        else
            size *= 2;      // Guess at a larger size (OS specific)
    }

    return str;
}

std::string format(const std::string fmt, va_list args) {

  int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
  std::string str;
  while (1) {     // Maximum two passes on a POSIX system...
      str.resize(size);
      int n = vsnprintf((char *)str.data(), size, fmt.c_str(), args);
      if (n > -1 && n < size) {  // Everything worked
          str.resize(n);
          return str;
      }
      if (n > -1)  // Needed size returned
          size = n + 1;   // For null char
      else
          size *= 2;      // Guess at a larger size (OS specific)
  }

  return str;
}

} /* hx3d */
