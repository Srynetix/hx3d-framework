/*
    File handling.
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

#ifndef HX3D_UTILS_FILE
#define HX3D_UTILS_FILE

#include <string>

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/resource.hpp"

namespace hx3d {

class File: public Resource {

public:
  File();
  ~File();

  /**
  Return the file content as a string.

  @return String
  */
  std::string toString();

  char* data;
  size_t size;

  ////////////////////

  /**
  Load an ascii file from a path.

  @param path Path to file
  */
  static Ptr<File> loadAsciiFile(std::string path);

  /**
  Load a binary file from a path.

  @param path Path to file
  */
  static Ptr<File> loadBinaryFile(std::string path);

private:
  #ifdef __ANDROID__
    /**
    Load an ascii file from an Android APK.

    @param path Path to file
    */
    static Ptr<File> loadAsciiFileAndroid(std::string path);
    /**
    Load a binary file from an Android APK.

    @param path Path to file
    */
    static Ptr<File> loadBinaryFileAndroid(std::string path);
    /**
    Read the file content as string.

    @param path Path to file
    */
    static std::string readAsString(std::string path);
  #endif

  /**
  Load an ascii file from a path on a desktop system.

  @param path Path to file
  */
  static Ptr<File> loadAsciiFileDesktop(std::string path);
  /**
  Load a binary file from a path on a desktop system.
  
  @param path Path to file
  */
  static Ptr<File> loadBinaryFileDesktop(std::string path);
};

} /* hx3d */

#endif
