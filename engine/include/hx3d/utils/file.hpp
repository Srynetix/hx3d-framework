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

#pragma once

#include <string>

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/resource.hpp"

namespace hx3d {

/**
@brief File loading abstraction
*/
class File: public Resource {

public:
  File();
  ~File();

  /**
  @brief Return the file content as a string.

  @return String
  */
  std::string toString();

  ////////////////////

  /**
  @brief Load an ascii file from a path.

  @param path Path to file

  @return File handler
  */
  static Pointer<File> loadAsciiFile(std::string path);

  /**
  @brief Load a binary file from a path.

  @param path Path to file

  @return File handler
  */
  static Pointer<File> loadBinaryFile(std::string path);

  /**
  @brief Write to an internal ascii file.

  @param path     Path to file
  @param content  Content
  */
  static void writeInternalAsciiFile(std::string path, std::string content);

  /**
  @brief Load an internal ascii file.

  @param path Path to file

  @return File handler
  */
  static Pointer<File> loadInternalAsciiFile(std::string path);

  /**
  @brief Get the file size

  @return Size
  */
  size_t getSize() const;

  /**
  @brief Get the file data as an 8-bit array

  @return 8-bit array
  */
  char* getData() const;

private:
  /// @brief File data in 8-bit array format
  char* data;
  /// @brief File size
  size_t size;

  #ifdef __ANDROID__
    /**
    @brief Load an ascii file from an Android APK.

    @param path Path to file
    */
    static Pointer<File> loadAsciiFileAndroid(std::string path);
    /**
    @brief Load a binary file from an Android APK.

    @param path Path to file
    */
    static Pointer<File> loadBinaryFileAndroid(std::string path);
    /**
    @brief Read the file content as string.

    @param path Path to file
    */
    static std::string readAsString(std::string path);

    static std::string getInternalPath();

  #elif __APPLE__

    #include "TargetConditionals.h"
    #ifdef TARGET_OS_IPHONE

      /**
      @brief Load an ascii file for iOS.

      @param path Path to file
      */
      static Pointer<File> loadAsciiFileiOS(std::string path);

      /**
      @brief Load a binary file for iOS.

      @param path Path to file
      */
      static Pointer<File> loadBinaryFileiOS(std::string path);

      /**
      @brief Read the file content as string.

      @param path Path to file
      */
      static std::string readAsString(std::string path);
    #endif
  #endif

  /**
  @brief Load an ascii file from a path on a desktop system.

  @param path Path to file
  */
  static Pointer<File> loadAsciiFileDesktop(std::string path);
  /**
  @brief Load a binary file from a path on a desktop system.

  @param path Path to file
  */
  static Pointer<File> loadBinaryFileDesktop(std::string path);
};

} /* hx3d */
