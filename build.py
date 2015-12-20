#!/usr/bin/env python

#     Main build program.
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

import argparse

from builds.dependencies import colorama

from builds.dependencies.colorama import Fore
from builds.dependencies.utils import Utils

from builds.linux   import LinuxBuilder
from builds.android import AndroidBuilder
from builds.windows import WindowsBuilder
from builds.macos   import MacOSBuilder
from builds.ios     import iOSBuilder

def create_cmakelists(game_build, args):
    content = "cmake_minimum_required(VERSION 2.8)\nproject(hx3d)\n\nadd_subdirectory(engine)\n"

    if args.test:
        content += "add_subdirectory(tests)"
    elif game_build:
        content += "add_subdirectory(game)"

    with open("CMakeLists.txt", "w+") as text_file:
        print("{}".format(content), file=text_file)

'''
Main
'''
def main():
    colorama.init(autoreset=True)

    available_systems = ["linux", "windows", "android", "macos", "ios"]

    parser = argparse.ArgumentParser(description='Build the project')
    parser.add_argument('system', help='System')
    parser.add_argument('-c','--clean', action="store_true", help='Clean')
    parser.add_argument('-d','--debug', action="store_true", help='Debug')
    parser.add_argument('-i','--install', action="store_true", help='Install')
    parser.add_argument('-t', '--test', action="store_true", help='Test')
    parser.add_argument('-e','--execute', action="store_true", help="Execute")
    parser.add_argument('-p','--profile', action="store_true", help="Profile")
    args = parser.parse_args()

    if Utils.direxists("game"):
        game_build = True
    else:
        game_build = False

        print()
        Utils.gPrint("[Game building OFF.]", Fore.BLUE)
    print()

    create_cmakelists(game_build, args)

    if args.system == "linux":
        LinuxBuilder(args, game_build).run()
    elif args.system == "windows":
        WindowsBuilder(args, game_build).run()
    elif args.system == "android":
        AndroidBuilder(args, game_build).run()
    elif args.system == "macos":
        MacOSBuilder(args, game_build).run()
    elif args.system == "ios":
        iOSBuilder(args, game_build).run()
    else:
        print("Unsupported. Available systems: ", available_systems)

if __name__ == "__main__":
    main()
