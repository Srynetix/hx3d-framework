/*
    Log management.
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
#include <map>

#include "hx3d/utils/file.hpp"

namespace hx3d {

/**
@brief Logging implementation: to log, use hx3d::Log.
*/
class LogImpl {

  /// @brief Log status
  enum class Status {
    /// @brief Informative message
    Info,
    /// @brief Shader message
    Shader,
    /// @brief Debug message
    Debug,
    /// @brief Error message
    Error
  };

public:
  LogImpl(const std::string& name);
  virtual ~LogImpl();

  /**
  @brief Display the log on the console.

  @param value True/False
  */
  void DisplayOnConsole(bool value);

  /**
  @brief Write an info message.

  @param fmt Text
  @param ... Arguments
  */
  void Info(const std::string fmt, ...);
  /**
  @brief Write a shader message.

  @param fmt Text
  @param ... Arguments
  */
  void Shader(const std::string fmt, ...);
  /**
  @brief Write a debug message.

  @param fmt Text
  @param ... Arguments
  */
  void Debug(const std::string fmt, ...);
  /**
  @brief Write an error message.

  @param fmt Text
  @param ... Arguments
  */
  void Error(const std::string fmt, ...);

private:
  bool _consoleOutput;
  std::string _name;
  Pointer<File> _file;

  /**
  @brief Write a message.

  @param text   Text
  @param status Status
  */
  void write(std::string text, Status status);
};

class Logger {
public:
  static LogImpl& getLogger(const std::string& name);

private:
  static std::map<std::string, Pointer<LogImpl>> _logs;
};

// / @brief Current log implementation
// static hx3d::LogImpl Log;

} /* hx3d */
