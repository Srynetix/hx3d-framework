#     Configuration file.
#
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

config = {}

config["game_name"] = "game"
config["debugger_name"] = "gdb"
config["compiler_name"] = "clang++"

config["android_toolchain_path"] = "/opt/custom-ndk"
config["android_build_type"] = "Debug"
config["android_package_name"] = "org.sryncorp.app"
config["android_activity_name"] = "OSEF"

config["ios_toolchain"] = "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer"
config["ios_platform"] = "OS"
