/*
    GL inclusions.
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

#ifdef __IPHONE_NA

  #include <OpenGLES/ES2/gl.h>

#elif __ANDROID__

  #include <GLES3/gl3.h>

#elif _WIN32

  #define DESKTOP_OPENGL
  #define WIN32_LEAN_AND_MEAN
  #include <WinDef.h>
  #include <WinGDI.h>

  /* Thanks Windows... ! */
  #undef near
  #undef far

  #include <GL/glew.h>

#elif __APPLE__

  #include "TargetConditionals.h"

    #if TARGET_IPHONE_SIMULATOR

      #include <OpenGLES/ES2/gl.h>

    #elif TARGET_OS_IPHONE

      #include <OpenGLES/ES2/gl.h>

    #elif TARGET_OS_MAC

      #define DESKTOP_OPENGL
      #include <GL/glew.h>

    #endif

#elif __linux__

  #define DESKTOP_OPENGL
  #include <epoxy/gl.h>
  // #include <epoxy/glx.h>

#endif

#include <SDL2/SDL.h>
