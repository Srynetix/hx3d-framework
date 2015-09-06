#
#     System check CMakeLists.
#     Copyright (C) 2015 Denis BOURGE
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License as published by the Free Software Foundation; either
#     version 2.1 of the License, or (at your option) any later version.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
#     USA

##################
## System check

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  IF(NOT IOS)
    set(MACOSX true)
  ENDIF()
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LINUX true)
ENDIF()

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies)
include_directories(SYSTEM ../dependencies/include)

if (ANDROID)
  link_directories(${DEPENDENCIES_DIR}/lib/android)
elseif(WIN32)
  link_directories(${DEPENDENCIES_DIR}/lib/windows)
elseif(MACOSX)
  set(CMAKE_MACOSX_RPATH ON)
  link_directories(${DEPENDENCIES_DIR}/lib/macos)
elseif(LINUX)
  link_directories(${DEPENDENCIES_DIR}/lib/linux)
elseif(IOS)
  link_directories(${DEPENDENCIES_DIR}/lib/ios)
endif()

#################
