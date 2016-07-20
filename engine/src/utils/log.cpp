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

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/string.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/core/configuration.hpp"

#include <iostream>
#include <sstream>

#ifdef __ANDROID__
  #include <android/log.h>
  #define LOG(msg) __android_log_print(ANDROID_LOG_VERBOSE, "hx3d", msg, 1)
#elif __APPLE__
  #include "TargetConditionals.h"
  #ifdef TARGET_OS_IPHONE
    #include <CoreFoundation/CoreFoundation.h>
    extern "C" {
      void NSLog(CFStringRef format, ...);
      void NSLogv(CFStringRef format, va_list args);
    }

    #define LOG(msg) NSLog(CFStringCreateWithCString(kCFAllocatorDefault, msg, kCFStringEncodingUTF8))
  #else
    #define LOG(msg) std::cout << msg << std::endl
  #endif
#else
  #define LOG(msg) std::cout << msg << std::endl
#endif

namespace hx3d {

LogImpl::LogImpl(): _consoleOutput(true) {
}

LogImpl::~LogImpl() {
}

void LogImpl::DisplayOnConsole(bool value) {
  _consoleOutput = value;
}

void LogImpl::Info(const std::string fmt, ...) {
  va_list args;
  va_start(args, fmt);
  write(format(fmt, args), Status::Info);
  va_end(args);
}

void LogImpl::Shader(const std::string fmt, ...) {
  va_list args;
  va_start(args, fmt);
  write(format(fmt, args), Status::Shader);
  va_end(args);
}

void LogImpl::Error(const std::string fmt, ...) {
  va_list args;
  va_start(args, fmt);
  write(format(fmt, args), Status::Error);
  va_end(args);
}

void LogImpl::Debug(const std::string fmt, ...) {
  // if (Core::Config()->get<bool>("log", "debug")) {
    va_list args;
    va_start(args, fmt);
    write(format(fmt, args), Status::Debug);
    va_end(args);
  // }
}

//////////////////////////////

void LogImpl::write(std::string text, Status status) {

    std::ostringstream oss;
    if (status == Status::Error) {
      oss << "E /!\\> ";
    }

    else if (status == Status::Shader) {
      oss << "S> ";
    }

    else if (status == Status::Info) {
      oss << "I> ";
    }

    else if (status == Status::Debug) {
      oss << "D> ";
    }

    oss << text;

    if (_consoleOutput) {
      LOG(oss.str().c_str());
    }
}

}
