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

#ifndef HX3D_UTILS_STRING
#define HX3D_UTILS_STRING

#include <string>
#include <cstdarg>
#include <vector>

namespace hx3d {

/**
@brief Format a string using `printf` notation.

@param fmt Text
@param ... Arguments

@return Formatted string
*/
std::string format(const std::string fmt, ...);

/**
@brief Format a string using `printf` notation (va_list version).

@param fmt Text
@param args Arguments

@return Formatted string
*/
std::string format(const std::string fmt, va_list args);

/**
@brief Split a string using a delimiter and a container.

@param s      String
@param delim  Delimiter
@param elems  Container

@return Split string
*/
std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);

/**
@brief Split a string using a delimiter.

@param s      String
@param delim  Delimiter

@return Split string
*/
std::vector<std::string> split(const std::string &s, char delim);

} /* hx3d */

#endif
