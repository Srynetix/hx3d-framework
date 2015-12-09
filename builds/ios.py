#     iOS target.
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

from .dependencies.builder import Builder
from .dependencies.utils import Utils
from .config import config

class iOSBuilder(Builder):
    def __init__(self, options, game):
        super().__init__("ios", options, game)

    def clean(self):
        Utils.rmdir(self.path)
        Utils.rmdir("{}/ios/assets".format(config["game_name"]))
        Utils.rmdir("{}/ios/build".format(config["game_name"]))
        Utils.rmdir("tests/ios/assets")
        Utils.rmdir("tests/ios/build")

    # Engine
    def prepare_engine(self):
        self.prepare_internal("cmake -G Xcode -DCMAKE_TOOLCHAIN_FILE=cmake/iOS.cmake -DIOS_PLATFORM={} ..".format(config["ios_platform"]))
    def build_engine(self):
        Utils.execCommand("cd {} && xcodebuild -target ALL_BUILD".format(self.path))

    # Game
    def build_game(self):
        game_name = config["game_name"]

        # Assets
        Utils.copydir("engine/assets", "{}/ios/assets".format(game_name))
        Utils.copydir("{}/assets".format(game_name), "{}/ios/assets".format(game_name))

        # Game
        Utils.execCommand("cd {}/ios && xcodebuild -configuration Debug".format(game_name))

    def install_game(self):
        Utils.execCommand("ios-deploy -b {}/ios/build/Debug-iphoneos/*.app".format(config["game_name"]))

    # Tests
    def build_tests(self):
        game_name = config["game_name"]

        # Assets
        Utils.copydir("engine/assets", "tests/ios/assets")
        Utils.copydir("tests/assets".format(game_name), "tests/ios/assets")

        # Game
        Utils.execCommand("cd tests/ios && xcodebuild -configuration Debug")

    def install_tests(self):
        Utils.execCommand("ios-deploy -b tests/ios/build/Debug-iphoneos/*.app")

    def debug_tests(self):
        pass
    def execute_tests(self):
        pass
